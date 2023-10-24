import torch
import numpy as np
import matplotlib.pyplot as plt
import os.path as path
import sys
sys.path.append(path.abspath("src/"))

from scipy.optimize import curve_fit
from norm_flow.planar import PlanarFlow
from norm_flow.utils import log_gaussian

torch.manual_seed(42)
device = "cpu"

# hyperparameters
n_dim = 1
n_layer = 4
batch_size = 4096
max_iter = 5000

def get_batch(x):
    x_tensor = torch.from_numpy(x).to(device).float()
    idx = torch.randint(0, len(x_tensor), (batch_size, )).to(device)
    return x_tensor[idx]

def main():
    st = np.random.normal(-2.5, 2.5, (50000,))
    st_truth = np.random.normal(-5, 4, (100000,))

    log_0 = lambda z: log_gaussian(z, -2.5, 2.5)
    log_k = lambda z: log_gaussian(z, -5, 4)

    model = PlanarFlow(n_dim, n_layer)
    m = model.to(device)
    sum(p.numel() for p in model.parameters() if p.requires_grad)

    optimizer = torch.optim.AdamW(model.parameters(), lr=0.01)

    x = st

    step = list()
    loss_train = list()

    for i in range(max_iter):
        if i % 100 == 0:
            print(f"{i} / {max_iter}")
        xb = get_batch(x)
        xk, sum_log_jacob = m(xb)
        loss = m.reverse_kld(xb, log_0, log_k)
        if i > 100:
            step.append(i)
            loss_train.append(loss.item())
        optimizer.zero_grad(set_to_none=True)
        loss.backward()
        optimizer.step()

    plt.plot(np.array(step), np.array(loss_train))

    with torch.no_grad():
        output, _ = m(torch.normal(-2.5, 2.5, (100000,)).to(device))
        output = output.cpu().numpy()
        plt.hist(output, bins=100)
        
        hist, bin_edges = np.histogram(output, bins=100)
        bin_centres = (bin_edges[:-1] + bin_edges[1:]) / 2

        def gauss(x, *p):
            A, mu, sigma = p
            return A * np.exp(-((x - mu) ** 2) / (2.0 * sigma**2))

        p0 = [3500.0, 0.0, 1.0]
        coeff, var_matrix = curve_fit(gauss, bin_centres, hist, p0=p0)

        print(coeff)

if __name__ == "__main__":
    main()
