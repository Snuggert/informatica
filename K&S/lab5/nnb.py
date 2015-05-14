import numpy as np
from scipy.stats import mode


class NNb:
    def __init__(self, X, c):
        self.n, self.N = X.shape
        self.X = X
        self.c = c

    def classify(self, x, k=1):
        d = self.X - np.tile(x.reshape(self.n, 1), self.N)
        dsq = np.sum(d * d, 0)
        minindex = np.argsort(dsq)[:k]
        return mode(self.c[minindex])[0][0]
