import math
import torch
import uproot
import numpy as np
import matplotlib.pyplot as plt


two_pi = torch.tensor([2 * math.pi]).float()
gen = torch.Generator()


def log_gaussian(x, mu, sigma):
    if len(x.shape) <= 1:
        n = 1
        x_2 = (x - mu) ** 2
    else:
        n = x.shape[1]
        x_2 = torch.sum((x - mu) ** 2, dim=1)
    two_pi = torch.tensor([2 * math.pi], dtype=x.dtype, device=x.device)
    sigma2 = torch.tensor([sigma**2], dtype=x.dtype, device=x.device)
    return (
        -0.5 * n * torch.log(two_pi) - 0.5 * n * torch.log(sigma2) - 0.5 / sigma2 * x_2
    )


def get_dateframe(file_path, tree_name):
    return uproot.open(f"{file_path}:{tree_name}").arrays(library="pd")


def quantile_scaling_(df, var_name):
    q25, q50, q75 = df[var_name].quantile([0.25, 0.5, 0.75])
    print(f"{var_name} 25%, 50%, 75% quantiles = {q25, q50, q75}")
    df[var_name] = (df[var_name] - q50) / (q75 - q25)
    print(f"{var_name} after scaling stats\n{df[var_name].describe()}")


def quantile_scaling(df, var_name):
    q25, q50, q75 = df[var_name].quantile([0.25, 0.5, 0.75])
    print(f"{var_name} 25%, 50%, 75% quantiles = {q25, q50, q75}")
    array = (df[var_name] - q50) / (q75 - q25)
    print(f"{var_name} after scaling stats\n{array.describe()}")
    return array.to_numpy(), (q25, q50, q75)


def get_batch(x, w, batch_size=1024):
    idx = torch.randint(0, len(w), (batch_size,), generator=gen)
    return x[idx], w[idx]


def train(
    model, x, w, x_val, w_val, max_iter, eval_step, batch_size, optimizer, scheduler
):
    step = list()
    loss_train = list()
    loss_train_step = list()
    loss_val_step = list()

    for i in range(max_iter):
        if i > 0 and i % eval_step == 0:
            with torch.no_grad():
                train_loss = np.array(loss_train[-eval_step:]).mean().item()
                val_loss = validate(model, x_val, w_val)
                print(
                    f"{i:6d} / {max_iter:6d}, "
                    f"train_loss={train_loss:.6f}, "
                    f"val_loss={val_loss:.6f}, "
                    f"lr = {scheduler.get_last_lr()[0]:.6f}"
                )
                step.append(i)
                loss_train_step.append(train_loss)
                loss_val_step.append(val_loss)
        xb, wb = get_batch(x, w, batch_size)
        z, log_det = model.inverse(xb)
        loss = torch.log(two_pi) + torch.mean(
            wb * (torch.sum(0.5 * z**2, -1) - log_det)
        )
        loss_train.append(loss.item())
        optimizer.zero_grad(set_to_none=True)
        loss.backward()
        optimizer.step()
        scheduler.step()

    return step, loss_train_step, loss_val_step


def train_val_split(df, x, w):
    x = torch.from_numpy(x).float()
    w = torch.from_numpy(w).float()
    N = x.shape[0]
    N_split = int(0.8 * N)
    x_val, w_val = x[N_split:], w[N_split:]
    x, w = x[:N_split], w[:N_split]
    N -= N_split
    return x, w, x_val, w_val, N


@torch.no_grad()
def validate(model, x_val, w_val):
    model.eval()
    z, log_det = model.inverse(x_val)
    loss = torch.log(two_pi) + torch.mean(
        w_val * (torch.sum(0.5 * z**2, -1) - log_det)
    )
    model.train()
    return loss.item()


def draw_dist2d2(x, z):
    fig = plt.figure(2, figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.plot(x[:, 0], x[:, 1], ".")
    plt.title("Observed distribution")
    plt.xlabel(r"$S_{T}$")
    plt.ylabel(r"sub b-jet $p_T$")

    plt.subplot(1, 2, 2)
    plt.plot(z[:, 0], z[:, 1], ".")
    plt.title("Latent distribution")
    plt.xlabel(r"$z_{0}$")
    plt.ylabel(r"$z_{1}$")
    plt.xlim([-4, 4])
    plt.ylim([-4, 4])
    plt.show()


def draw_dist2d3(x_, x_trans_, z_):
    plt.figure(2, figsize=(15, 4))
    plt.subplot(1, 3, 1)
    plt.plot(x_[:, 0], x_[:, 1], ".")
    plt.title("Observed distribution")
    plt.xlabel(r"$S_{T}$")
    plt.ylabel(r"sub b-jet $p_T$")

    plt.subplot(1, 3, 2)
    plt.plot(x_trans_[:, 0], x_trans_[:, 1], ".")
    plt.title("Transformed distribution")
    plt.xlabel(r"$S_{T}$")
    plt.ylabel(r"sub t-quark $p_T$")

    plt.subplot(1, 3, 3)
    plt.plot(z_[:, 0], z_[:, 1], ".")
    plt.title("Latent distribution")
    plt.xlabel(r"$z_{0}$")
    plt.ylabel(r"$z_{1}$")
    plt.xlim([-4, 4])
    plt.ylim([-4, 4])
    plt.show()


def draw_hist3(x_, x_trans_, x_truth_, w, w_unfold, w_t):
    plt.figure()
    _, bins, _ = plt.hist(
        x_truth_, bins=40, range=(0, 800), histtype="step", label="Truth", weights=w_t
    )
    plt.hist(
        x_trans_, bins=bins, histtype="step", label="Normalising Flow", weights=w_unfold
    )
    plt.hist(x_, bins=bins, histtype="step", label="Reco", weights=w)
    plt.xlim([0, 800])
    plt.ylim([0, 11.8])
    plt.text(100, 10, "Normalising Flow Method")
    plt.legend()
    plt.show()
