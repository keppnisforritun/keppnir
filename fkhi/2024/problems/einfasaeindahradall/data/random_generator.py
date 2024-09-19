#!/usr/bin/python3
import sys
import random

def product(l):
    res = 1
    for x in l:
        res *= x
    return res

random.seed(int(sys.argv[-1]))

max_p = int(sys.argv[1])
max_q = int(sys.argv[2])
max_opt = int(sys.argv[3])
n, dims = 0, []

if sys.argv[4][0].isdigit():
    n = int(sys.argv[4])
    dims = [1 for _ in range(n)]
    while True:
        i = random.randint(0, n - 1)
        dims[i] += 1
        if product(dims) > max_opt:
            dims[i] -= 1
            break
else:
    typ = sys.argv[4]
    if typ == "unique":
        n = 1
        dims = [1 for _ in range(10)]
    if typ == "long":
        n = 10
        dims = [1 for _ in range(10)]
    if typ == "exact":
        n = 6
        dims = [10 for _ in range(6)]
    if typ == "spread":
        n = 10
        dims = [4 for _ in range(8)] + [5, 3]
        random.shuffle(dims)
    if typ == "factorial":
        n = 9
        dims = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        random.shuffle(dims)

sys.stdout.write(f"{n}\n")
bounds = []
for i in range(n):
    offs = random.randint(-2 * dims[i], 2 * dims[i])
    if max_p > 1000:
        offs = random.randint(0, dims[i] // 2)
        # negative case already tested in smaller data
        # done to reduce data size
    bounds.append((offs, offs + dims[i] - 1))
    sys.stdout.write(f"{offs} {offs + dims[i] - 1}")
    if i != n - 1:
        sys.stdout.write(" ")
    else:
        sys.stdout.write("\n")

cur_p = random.randint(9 * max_p // 10, max_p)
sys.stdout.write(f"{cur_p}\n")
for j in range(cur_p):
    for i in range(n):
        val = random.randint(bounds[i][0], bounds[i][1])
        sys.stdout.write(f"{val}")
        if i != n - 1:
            sys.stdout.write(" ")
        else:
            sys.stdout.write("\n")

cur_q = random.randint(9 * max_q // 10, max_q)
sys.stdout.write(f"{cur_q}\n")
for j in range(cur_q):
    for i in range(n):
        a, b = 0, 0
        if random.randint(1, 1000) == 1:
            a = random.randint(-10 ** 9, 10 ** 9)
            b = random.randint(-10 ** 9, 10 ** 9)
        else:
            a = random.randint(bounds[i][0], bounds[i][1])
            b = random.randint(bounds[i][0], bounds[i][1])
        if a > b:
            a, b = b, a
        sys.stdout.write(f"{a} {b}")
        if i != n - 1:
            sys.stdout.write(" ")
        else:
            sys.stdout.write("\n")

