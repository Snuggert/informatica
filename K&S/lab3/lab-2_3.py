import random
import numpy
import matplotlib.pyplot as pyplot

def inverse_transform_sampling(lmbd, sample_size):
    """ CDF = 1 - e^(lambda x) it's inverse is -ln(-x+1)/lambda. """
    samples = []
    for i in range(sample_size):
        u = random.random()
        samples.append(- numpy.log(-u + 1) / lmbd)
    return samples

samples = inverse_transform_sampling(1, 1000)
n, bins, patches = pyplot.hist(samples)
pyplot.show()

lmbd = 1 / numpy.mean(samples)
print("lambda = ", lmbd)
