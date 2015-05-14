import re
import numpy
import pylab

def male_or_female(Mmu, Fmu, Msigma, Fsigma, test_data):
    Mpost = normpdf(test_data[0], Mmu[0], Msigma[0]) * \
            normpdf(test_data[1], Mmu[1], Msigma[1]) * \
            normpdf(test_data[2], Mmu[2], Msigma[2])
    Fpost = normpdf(test_data[0], Fmu[0], Fsigma[0]) * \
            normpdf(test_data[1], Fmu[1], Fsigma[1]) * \
            normpdf(test_data[2], Fmu[2], Fsigma[2])

    if(Mpost > Fpost):
        return 'M'
    else:
        return 'F'


# Normal probability density function
def normpdf(x, mu, sigma):
    u = (x - mu) / abs(sigma)
    y = (1 / (numpy.sqrt(2 * numpy.pi) * abs(sigma))) * numpy.exp(-u * u / 2)
    return y


def main():
    ptrn = '^([MF])\s?,([1-9][0-9]*|0),([1-9][0-9]*|0),([1-9][0-9]*.?[0-9]|0)$'
    lines = [line.strip() for line in open('biometrie2014.csv')]
    Mdata = []
    Fdata = []
    for line in lines:
        searchResult = re.search(ptrn, line)
        if searchResult:
            if searchResult.group(1) == 'M':
                Mdata.append([float(searchResult.group(2)),
                              float(searchResult.group(3)),
                              float(searchResult.group(4))])
            if searchResult.group(1) == 'F':
                Fdata.append([float(searchResult.group(2)),
                              float(searchResult.group(3)),
                              float(searchResult.group(4))])
        else:
            print('line did not pass regex')

    Mdata = numpy.array(Mdata)
    Fdata = numpy.array(Fdata)

    Mmu = numpy.median(Mdata, axis=0)
    Fmu = numpy.median(Fdata, axis=0)

    Msigma = numpy.sqrt(numpy.var(Mdata, axis=0))
    Fsigma = numpy.sqrt(numpy.var(Fdata, axis=0))

    xWeight = numpy.arange(0, 150, 0.1)
    Mweight = normpdf(xWeight, Mmu[0], Msigma[0])
    Fweight = normpdf(xWeight, Fmu[0], Fsigma[0])

    pylab.plot(xWeight, Mweight, color='red')
    pylab.plot(xWeight, Fweight, color='blue')
    pylab.legend(['man', 'vrouw'])
    pylab.xlabel("Weight in Kg")
    pylab.show()

    xHeight = numpy.arange(140, 210, 0.1)
    Mheight = normpdf(xHeight, Mmu[1], Msigma[1])
    Fheight = normpdf(xHeight, Fmu[1], Fsigma[1])

    pylab.plot(xHeight, Mheight, color='red')
    pylab.plot(xHeight, Fheight, color='blue')
    pylab.legend(['man', 'vrouw'])
    pylab.xlabel("Height in cm")
    pylab.show()

    xSize = numpy.arange(30, 50, 0.1)
    Msize = normpdf(xSize, Mmu[2], Msigma[2])
    Fsize = normpdf(xSize, Fmu[2], Fsigma[2])

    pylab.plot(xSize, Msize, color='red')
    pylab.plot(xSize, Fsize, color='blue')
    pylab.xlabel("Shoe size")
    pylab.legend(['man', 'vrouw'])
    pylab.show()

    print(male_or_female(Mmu, Fmu, Msigma, Fsigma, [60, 183, 42]))

    Mtest = 0
    Ftest = 0

    for m in Mdata:
        if(male_or_female(Mmu, Fmu, Msigma, Fsigma, m) == 'M'):
            Mtest = Mtest + 1
        else:
            Ftest = Ftest + 1
    print(Mtest, Ftest)

    Mtest = 0
    Ftest = 0

    for f in Fdata:
        if(male_or_female(Mmu, Fmu, Msigma, Fsigma, f) == 'F'):
            Ftest = Ftest + 1
        else:
            Mtest = Mtest + 1
    print(Mtest, Ftest)

if __name__ == '__main__':
    main()
