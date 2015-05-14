import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize

th1 = 2
th2 = .5

x = np.linspace(0, 20, 200)  # Get 100 numbers linearly spaced between 0-10.
y = th1 * np.sin(th2 * x) + 0.3 * np.random.randn(*x.shape)


def j(th):
    th1, th2 = th
    print("j", th1, th2)
    return np.linalg.norm(y - th1 * np.sin(th2 * x)) ** 2


def jac(th):
    th1, th2 = th
    return_matrix = np.array([
        np.sum(2 * np.sin(x * th2) * (th1 * np.sin(x * th2) - y)),
        np.sum(2 * x * th1 * np.cos(x * th2) * (th1 * np.sin(x * th2) - y))])
    print("jac", return_matrix.T)
    return return_matrix

res = minimize(j, (1., 0.), jac=jac, method='CG')
print(res)

eth1, eth2 = res.x
plt.plot(x, y, 'xb')
plt.plot(x, eth1 * np.sin(eth2 * x), 'b')
plt.plot(x, th1 * np.sin(th2 * x), 'g')
plt.show()
