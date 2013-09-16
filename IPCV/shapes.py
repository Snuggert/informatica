import pylab as pl

def plot_shape(points, color='r'):
    for i in range(len(points)):
        j = (i + 1) % len(points)
        x = [points[i][0], points[j][0]]
        y = [points[i][1], points[j][1]]
        pl.plot(x, y, color)

if __name__ == '__main__':
    plot_shape([(0, 0), (1, 0), (1, 1), (0, 1)], 'b')

    # plot_shape([(5, 3), (6, 3), (6, 4), (5, 4)])
    # lim = (-1, 7)

    # plot_shape([(0, 0), (1, 0), (1.5, 1), (0.5, 1)])
    # lim = (-1, 2.5)

    # plot_shape([(1, 1), (6, 3), (8, 6), (3, 4)])
    # lim = (-1, 9)

    plot_shape([(0, 0), (2, 1), (1, 3), (-1, 2)])
    lim = (-2, 4)

    pl.xlim(lim)
    pl.ylim(lim)
    pl.show()
