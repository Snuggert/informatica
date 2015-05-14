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
A = plt.dot(U, plt.sqrt(L))  # required transform matrix

X = plt.randn(4, n)  # 4xn matrix with each element ~ N(0,1)
Y = plt.dot(A, X) + plt.tile(mu, n)  # 4xn each column vector ~N(mu,Sigma)

f, axarr = plt.subplots(4, 4, sharex=True, sharey=True)
for i in range(0, len(Y)):
    for j in range(0, len(Y)):
        if(i == j):
            axarr[i][j].set_title(str(i) + ',' + str(j))
            axarr[i][j].axis('off')
            continue

        axarr[i][j].plot(Y[i], Y[j], 'xg')
        axarr[i][j].set_title(str(i) + ',' + str(j))

plt.setp([a.get_xticklabels() for a in axarr[0, :]], visible=False)
plt.setp([a.get_yticklabels() for a in axarr[:, 1]], visible=False)
plt.tight_layout()
# scatter plot of N(mu,Sigma) distribution
plt.savefig('scatter.pdf')
plt.clf()
