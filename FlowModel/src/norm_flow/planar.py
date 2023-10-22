import torch
import torch.nn as nn
import numpy as np


class PlanarBlock(nn.Module):
    def __init__(self, n_dim):
        super().__init__()
        lim_w = np.sqrt(2.0 / np.prod(n_dim))
        lim_u = np.sqrt(2.0)

        self.u = nn.Parameter(torch.empty(n_dim).float())
        self.w = nn.Parameter(torch.empty(n_dim).float())
        self.b = nn.Parameter(torch.zeros(1).float())

        nn.init.uniform_(self.u, -lim_u, lim_u)
        nn.init.uniform_(self.w, -lim_w, lim_w)

        self.h = nn.Tanh()
        self.h_ = lambda x: (1 - self.h(x) ** 2)

    def constraint_u(self):
        # constraint w.T * u > -1
        wu = torch.sum(self.w * self.u)
        wu_term = torch.log(1 + torch.exp(wu)) - 1 - wu
        return self.u + wu_term * self.w / (torch.sum(self.w**2) + 1e-15)

    def forward(self, z):
        lin = self.w @ z.reshape(z.shape[0], -1).T + self.b
        wu = torch.sum(self.w * self.u)
        u = self.constraint_u()
        # next
        active = self.h(lin).unsqueeze(-1) if len(z.shape) > 1 else self.h(lin)
        z_ = z + u * active
        wu = torch.sum(self.w * u)
        log_det = torch.log(torch.abs(1 + wu * self.h_(lin)) + 1e-15)
        return z_, log_det


class PlanarFlow(nn.Module):
    def __init__(self, n_dim, n_layer):
        super().__init__()
        self.blocks = nn.Sequential(*(PlanarBlock(n_dim) for _ in range(n_layer)))

    def forward(self, z):
        sum = torch.zeros(z.shape[0], dtype=z.dtype, device=z.device)
        for block in self.blocks:
            z, log_det = block(z)
            sum += log_det
        return z, sum

    def forward_kld(self, x, log_q0):
        # x is sampled from target distribution
        if not hasattr(self.blocks[0], "inverse"):
            raise RuntimeError(
                "can not calculate forward kld for flows without inverse()"
            )
        log_q = torch.zeros(len(x), dtype=x.dtype, device=x.device)
        z = x
        for i in range(len(self.blocks) - 1, -1, -1):
            z, log_det = self.blocks[i].inverse(z)
            log_q += log_det
        log_q += log_q0(z)
        return -torch.mean(log_q)

    def reverse_kld(self, x, log_q0, log_pz, beta=1.0):
        # x is sampled from base distribution
        log_q_ = log_q0(x)
        z = x
        log_q = torch.zeros_like(log_q_)
        log_q += log_q_
        for block in self.blocks:
            z, log_det = block(z)
            log_q -= log_det
        log_p = log_pz(z)
        return torch.mean(log_q) - beta * torch.mean(log_p)
