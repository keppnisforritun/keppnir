#!/usr/bin/python3
import sys, random, math

fixed = [1, 2, 3, 6, 7, 9, 10, 11, 16, 500500, 10 ** 10, 9999878909, 9999878910]

random.seed(int(sys.argv[-1]))

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])

if random.randint(1, 2) == 1:
    x = 1
    while x in fixed:
        x = random.randint(min_n, max_n)
    print(x)
else:
    y = 1
    while y in fixed:
        y = random.uniform(math.log(min_n), math.log(max_n))
        y = int(round(math.exp(y)))
        y = max(y, min_n)
        y = min(y, max_n)
    print(y)
