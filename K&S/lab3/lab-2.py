import random
import pylab
import numpy


def main():
    n = 1000
    pairs = []
    for i in range(n):
        pairs.append([random.random(), random.random()])
    pairs = numpy.array(pairs)
    pylab.plot(pairs[:, 0], pairs[:, 1], 'ro')
    pylab.show()

    ibm_pairs = numpy.column_stack((ibm_random(1000, random.random()),
                                    ibm_random(1000, random.random())))
    ibm_pairs = numpy.array(ibm_pairs)
    pylab.plot(ibm_pairs[:, 0], ibm_pairs[:, 1], 'ro')
    pylab.show()
    # i see little difference, yet there is a predictable pattern.


def ibm_random(n, x0):
    random_ibm = [x0]
    m = numpy.power(2.0, 31)
    for i in range(n):
        random_ibm.append(((65539.0 * random_ibm[i]) + 0.0) % m)
    random_ibm.pop(0)

    random_ibm = random_ibm / m
    return random_ibm

if __name__ == '__main__':
    main()
