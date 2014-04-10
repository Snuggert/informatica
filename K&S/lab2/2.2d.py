import random


def main():
    p = 0.6
    U = [0, 0]
    for index in range(100000000):
        if random.random() < p:
            U[0] += 1
        else:
            U[1] += 1
    test_p = U[0] / 100000000.0
    print test_p, p

if __name__ == '__main__':
    main()
