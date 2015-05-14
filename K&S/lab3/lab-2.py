import random
import pylab
import numpy

def ibm_random(n, x0):
    random_ibm = [x0]
    m = numpy.power(2.0, 31)
    for i in range(n):
        random_ibm.append(((65539.0 * random_ibm[i]) + 0.0) % m)
    random_ibm.pop(0)

    random_ibm = random_ibm / m
    return random_ibm

n = 1000
pairs = []
for i in range(n):
    pairs.append([random.random(), random.random()])
pairs = numpy.array(pairs)
pylab.plot(pairs[:, 0], pairs[:, 1], 'ro')
pylab.show()

ibm_pairs = numpy.column_stack((ibm_random(n, random.random()),
                                ibm_random(n, random.random())))
ibm_pairs = numpy.array(ibm_pairs)
pylab.plot(ibm_pairs[:, 0], ibm_pairs[:, 1], 'ro')
pylab.show()
# To the naked eye the pairs seem equally well distributed with both RNGs.
