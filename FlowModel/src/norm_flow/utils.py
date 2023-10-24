import math
import torch
import uproot

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


@torch.no_grad()
def validate(model, x_val, w_val):
    model.eval()
    z, log_det = model.inverse(x_val)
    loss = torch.log(two_pi) + torch.mean(
        w_val * (torch.sum(0.5 * z**2, -1) - log_det)
    )
    model.train()
    return loss.item()
