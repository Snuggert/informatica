import random

p = 0.6
upper_bound = 100000000
U = [0, 0]
for index in range(upper_bound):
    if random.random() < p:
        U[0] += 1
    else:
        U[1] += 1
test_p = U[0] / upper_bound
print(test_p, p)
