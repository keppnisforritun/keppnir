#!/usr/bin/python3
import sys, itertools
n = int(sys.stdin.readline())
bounds = list(map(int, sys.stdin.readline().split()))
l = [bounds[2 * i] for i in range(n)]
r = [bounds[2 * i + 1] for i in range(n)]
coeff = [1 for _ in range(n)]
for i in range(1, n):
    coeff[i] = coeff[i - 1]
    coeff[i] *= bounds[2 * i - 1] - bounds[2 * i - 2] + 1
opts = coeff[-1] * (bounds[-1] - bounds[-2] + 1)
cnts = [0 for _ in range(opts)]
p = int(sys.stdin.readline())
for _ in range(p):
    coord = 0
    for (i, x) in enumerate(map(int, sys.stdin.readline().split())):
        coord += coeff[i] * (x - bounds[2 * i])
    cnts[coord] += 1
for i in range(n):
    for j in range(coeff[i], opts):
        coord = j
        if i != n - 1:
            coord %= coeff[i + 1]
        if coord >= coeff[i]:
            cnts[j] += cnts[j - coeff[i]]
q = int(sys.stdin.readline())
for _ in range(q):
    query = list(map(int, sys.stdin.readline().split()))
    done = False
    for j in range(n):
        if query[2 * j] > bounds[2 * j + 1]:
            done = True
        if query[2 * j + 1] < bounds[2 * j]:
            done = True
        query[2 * j] = max(query[2 * j], bounds[2 * j])
        query[2 * j + 1] = min(query[2 * j + 1], bounds[2 * j + 1])
    if done:
        sys.stdout.write("0\n")
        continue
    a = [coeff[i] * (query[2 * i] - l[i] - 1) for i in range(n)]
    b = [coeff[i] * (query[2 * i + 1] - l[i]) for i in range(n)]
    cur, neg, ev = 0, 0, True
    for i in range(n):
        cur += b[i]
    res = cnts[cur]
    for it in range(1, 1 << n):
        msk = it ^ (it >> 1)
        ev = not ev
        togg = (msk ^ (it - 1) ^ ((it - 1) >> 1)).bit_length() - 1
        if msk & (1 << togg):
            neg += a[togg] < 0
            cur += a[togg]
            cur -= b[togg]
        else:
            neg -= a[togg] < 0
            cur -= a[togg]
            cur += b[togg]
        if neg == 0:
            val = cnts[cur]
            if ev:
                res += val
            else:
                res -= val
    sys.stdout.write(f"{res}\n")

