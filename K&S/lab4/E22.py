import pylab as plt

n = 1000
mu = [[0],
      [0],
      [0],
      [0]]
Sigma = [[3.01602775, 1.02746769, -3.60224613, -2.08792829],
         [1.02746769, 5.65146472, -3.98616664, 0.48723704],
         [-3.60224613, -3.98616664, 13.04508284, -1.59255406],
         [-2.08792829, 0.48723704, -1.59255406, 8.28742469]]

d, U = plt.eig(Sigma)  # Sigma = U L Ut
L = plt.diagflat(d)
A = plt.dot(U, plt.sqrt(L))  # Required transform matrix.

X = plt.randn(4, n)  # 4*n matrix with each element ~ N(0,1)
# 4*n each column vector ~N(mu,Sigma), random draws from distribution.
Y = plt.dot(A, X) + plt.tile(mu, n)

Ybar = [[avg] for avg in plt.mean(Y, 1)]  # Mean along the 1 axis.
Yzm = Y - plt.tile(Ybar, n)  # Subtract mean from each column.
# Estimator for covariance matrix.
S = plt.dot(Yzm, plt.transpose(Yzm)) / n - 1

print(Ybar, S)
