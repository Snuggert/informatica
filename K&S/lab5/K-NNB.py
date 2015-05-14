import matplotlib.pyplot as plt
import numpy as np
from nnb import NNb


def cnvt(s):
    s = s.decode("utf-8")
    tab = {'Iris-setosa': 1.0, 'Iris-versicolor': 2.0, 'Iris-virginica': 3.0}
    if s in tab:
        return tab[s]
    else:
        return -1.0

k = 9

XC = np.loadtxt('iris.data', delimiter=',', dtype=float, converters={4: cnvt})
ind = np.arange(150)  # indices into the dataset
ind = np.random.permutation(ind)  # random permutation
# Split set in 90:60 LearningSet:TestSet
L = ind[0:90]  # learning set indices
T = ind[90:]  # test set indices

# Learning Set
X = np.transpose(XC[L, 0:4])
nnc = NNb(X, XC[L, -1])

# Classification of Test Set
c = np.zeros(len(T))
for i in np.arange(len(T)):
    c[i] = nnc.classify(XC[T[i], 0:4], k)

# Confusion Matrix
CM = np.zeros((3, 3))
for i in range(3):
    for j in range(3):
        CM[i, j] = np.sum(np.logical_and(XC[T, 4] == (i + 1), c == (j + 1)))
print(CM)

# Plot Test Set
color = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
f, axarr = plt.subplots(4, 4, sharex=True, sharey=True)

for i in range(4):
    for j in range(4):
        if i == j:
            axarr[i][j].axis('off')
            continue
        axarr[i][j].scatter(XC[T, i], XC[T, j], marker='s', s=60,
                            edgecolor=color[XC[T, 4].astype(int) - 1],
                            facecolor=[1, 1, 1])
        axarr[i][j].scatter(XC[T, i], XC[T, j], marker='x', s=30,
                            edgecolor=color[c.astype(int) - 1])

        axarr[i][j].set_xlim([0, 8])
        axarr[i][j].set_ylim([0, 8])

plt.setp([a.get_xticklabels() for a in axarr[0, :]], visible=False)
plt.setp([a.get_yticklabels() for a in axarr[:, 1]], visible=False)
plt.tight_layout()
plt.savefig('nnbtest.pdf')
plt.clf()
