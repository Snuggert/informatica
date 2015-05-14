import pylab
import numpy
from scipy.stats import norm
import random


# function for standard normal equation
def sne(x):
    return numpy.power(numpy.e, -0.5 * x * x) / numpy.sqrt(2 * numpy.pi)

def main():
    # 1000 spaced numbers
    x = numpy.arange(-5.0, 5.0, 0.01)
    y1 = sne(x)

    pylab.plot(x, y1)
    pylab.show()

    y = norm.cdf(x)
    x2 = []
    for i in range(1000):
        x2.append(random.normalvariate(0, 1))

    values, base = numpy.histogram(x2, bins=1000)
    normal_values = values / float(values.sum())
    #evaluate the cumulative
    cumulative = numpy.cumsum(normal_values)
    # plot the cumulative function
    pylab.plot(base[:-1], cumulative, 'ro')

    pylab.plot(x, y, color="black")
    pylab.xlabel("Variate")
    pylab.ylabel("Cumulative Probability")
    pylab.show()

if __name__ == '__main__':
    main()
