#!/usr/bin/python3
import sys, random

random.seed(int(sys.argv[-1]))

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
typ = sys.argv[3]

n = 2 * random.randint(min_n // 2, max_n // 2) + 1
xs = []

if typ == "uniform":
    a, b = 0, 0
    while a == 0:
        a = random.uniform(0, 1e9)
    while b == 0:
        b = random.uniform(0, 1e9)
    if a > b:
        a, b = b, a
    for _ in range(n):
        xs.append(random.uniform(a, b))

if typ == "equal":
    x = 0
    while x == 0:
        x = random.uniform(0, 1e9)
    for _ in range(n):
        xs.append(x)

if typ == "outliers":
    a, b = random.uniform(1e0, 1e2), random.uniform(1e8, 1e9)
    if random.randint(1, 2) == 1:
        a, b = b, a
    for _ in range(n):
        xs.append(a)
    for _ in range(max(5, n // 1000)):
        i = random.randint(0, len(xs) - 1)
        xs[i] = b

if typ == "exponential":
    for _ in range(n):
        x = random.uniform(0, 9)
        xs.append(10 ** x)

print(n)
print(" ".join(["{:6f}".format(x) for x in xs]))
