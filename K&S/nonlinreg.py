import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize

th1 = 2
th2 = .5

x = np.linspace(0, 10, 100)  # Get 100 numbers linearly spaced between 0-10.
y = th1 * np.sin(th2 * x) + 0.3 * np.random.randn(*x.shape)
X = np.vstack((np.ones(x.shape), x)).T


def j(th):
    th1, th2 = th
    print(th1, th2)
    return np.linalg.norm(y - th1 * np.sin(th2 * x)) ** 2


def jac(th):
    return 2 * (np.dot(np.dot(X.T, X), th) - np.dot(X.T, y))

res = minimize(j, (0, 0), jac=jac, method='CG')
print res

eth1, eth2 = res.x
plt.plot(x, y, 'xb')
plt.plot(x, eth1 * np.sin(eth2 * x), 'b')
plt.plot(x, th1 * np.sin(th2 * x), 'g')
plt.show()
