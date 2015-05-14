import matplotlib.pyplot as plt
import numpy as np


# function for norm pdf
def ne(x, mu, sigma, p):
    u = (x - mu) / abs(sigma)
    y = (1. / (np.sqrt(2. * np.pi) * abs(sigma))) * np.exp(-u * u / 2.)
    return y * p

# linearly spaced numbers in range -5 to 15
x = np.arange(-5.0, 15.0, 0.01)
y1 = ne(x, 4., 1., 0.3)
y2 = ne(x, 7., 2., 0.7)
y3 = np.zeros_like(x)
for i, num in enumerate(y1):
    y3[i] = ((num + y2[1]) / 2.)
y3 = (y3 / np.max(y3)) * 10.
y_intersect = np.abs(y1 - y2)

plt.plot(x, y1, 'b')
plt.plot(x, y2, 'r')
plt.plot(x, y3, 'r')
plt.plot(x, y_intersect, 'y')
# plt.scatter(x[minindex], y2[minindex], 'b')
plt.ylim(0.0, 1.0)
plt.show()
