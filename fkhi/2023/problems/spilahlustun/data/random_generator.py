#!/usr/bin/python3
import random
import sys

random.seed(sys.argv[-1])

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
min_q = int(sys.argv[3])
max_q = int(sys.argv[4])
special = sys.argv[5]

n = random.randint(min_n, max_n)
q = random.randint(min_q, max_q)
print("{} {}".format(n, q))

if special == "benni":
    for i in range(n-2):
        print("{} {}".format(i+1, i+3))
        q -= 1
        if q == 0:
            break
for i in range(q):
    sz = random.randint(1, n)
    a = random.randint(1, n - sz + 1)
    b = a + sz - 1
    print("{} {}".format(a, b))
