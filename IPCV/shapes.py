import pylab as pl

def plot_shape(points, color='r'):
    for i in range(len(points)):
        j = (i + 1) % len(points)
        x = [points[i][0], points[j][0]]
        y = [points[i][1], points[j][1]]
        pl.plot(x, y, color)

if __name__ == '__main__':
    plot_shape([(0, 0), (1, 0), (1, 1), (0, 1)], 'k')
    pl.annotate('Black = original', (-1, 6))

    plot_shape([(5, 3), (6, 3), (6, 4), (5, 4)], 'b')
    pl.annotate('Blue = T1', (-1, 5.5))

    plot_shape([(0, 0), (1, 0), (1.5, 1), (0.5, 1)], 'g')
    pl.annotate('Green = T2', (-1, 5))
 
    plot_shape([(1, 1), (6, 3), (8, 6), (3, 4)], 'y')
    pl.annotate('Yellow = T3', (-1, 4.5))

    plot_shape([(0, 0), (2, 1), (1, 3), (-1, 2)], 'r')
    pl.annotate('Red = T4', (-1, 4))

    lim = (-2, 9)



    pl.xlim(lim)
    pl.ylim(lim)
    pl.show()
