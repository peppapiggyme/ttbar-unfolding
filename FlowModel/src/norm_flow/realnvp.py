"""
2-D RealNVP architecture
Adopted from https://github.com/xqding/RealNVP
"""

import torch
import torch.nn as nn
import torch.nn.init as init

dual_layer = [[1.0, 0.0], [0.0, 1.0]]


class FeedForward(nn.Module):
    def __init__(self, input_dim, hidden_dim):
        super().__init__()
        self.act = nn.Tanh()
        self.ff = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            self.act,
            nn.Linear(hidden_dim, hidden_dim),
            self.act,
            nn.Linear(hidden_dim, input_dim),
            self.act,
        )

    def forward(self, x):
        return self.ff(x)


class Affine_Coupling(nn.Module):
    def __init__(self, mask, hidden_dim):
        super().__init__()
        self.input_dim = len(mask)
        self.hidden_dim = hidden_dim

        self.mask = nn.Parameter(mask, requires_grad=False)
        self.scale = nn.Parameter(torch.Tensor(self.input_dim))
        init.normal_(self.scale)

        self.s = FeedForward(self.input_dim, self.hidden_dim)
        self.t = FeedForward(self.input_dim, self.hidden_dim)

    def _compute_scale(self, x):
        return self.s(x * self.mask) * self.scale

    def _compute_translation(self, x):
        return self.t(x * self.mask)

    def forward(self, x):
        s = self._compute_scale(x)
        t = self._compute_translation(x)

        y = self.mask * x + (1 - self.mask) * (x * torch.exp(s) + t)
        logdet = torch.sum((1 - self.mask) * s, -1)

        return y, logdet

    def inverse(self, y):
        s = self._compute_scale(y)
        t = self._compute_translation(y)

        x = self.mask * y + (1 - self.mask) * ((y - t) * torch.exp(-s))
        logdet = torch.sum((1 - self.mask) * (-s), -1)

        return x, logdet


class RealNVP(nn.Module):
    def __init__(self, masks, hidden_dim):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.masks = nn.ParameterList(
            [nn.Parameter(torch.Tensor(m), requires_grad=False) for m in masks]
        )

        self.affine_couplings = nn.ModuleList(
            [
                Affine_Coupling(self.masks[i], self.hidden_dim)
                for i in range(len(self.masks))
            ]
        )

    def forward(self, x):
        y = x
        logdet_tot = 0

        for i in range(len(self.affine_couplings)):
            y, logdet = self.affine_couplings[i](y)
            logdet_tot = logdet_tot + logdet

        return y, logdet_tot

    def inverse(self, y):
        x = y
        logdet_tot = 0

        for i in range(len(self.affine_couplings) - 1, -1, -1):
            x, logdet = self.affine_couplings[i].inverse(x)
            logdet_tot = logdet_tot + logdet

        return x, logdet_tot


class EncoderDecoder_ReadlNVP(nn.Module):
    def __init__(self, masks, hidden_dim):
        super().__init__()
        self.encoder = RealNVP(masks[0], hidden_dim[0])
        self.decoder = RealNVP(masks[1], hidden_dim[1])

    def forward(self, x):
        x0, logdet_en = self.encoder.inverse(x)
        y, logdet_de = self.decoder.forward(x0)
        return x0, logdet_en, y, logdet_de

    def inverse(self, y):
        x0, logdet_de = self.decoder.inverse(y)
        x, logdet_en = self.encoder.forward(x0)
        return x0, logdet_de, x, logdet_en
