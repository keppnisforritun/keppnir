#!/usr/bin/python3
import random, math, sys

random.seed(int(sys.argv[-1]))

extra = eval(sys.argv[1])
tiny = eval(sys.argv[2])

rad = 18732304883898125

def get_p(n):
    for x in [5, 13, 17, 29, 37, 41]:
        if n % x == 0:
            return x
    return 1

def mAp3(p):
    while True:
        c = random.randint(1, p - 1)
        if pow(c, (p - 1) // 2, p) == p - 1:
            return pow(c, (p - 1) // 4, p)

def mAp4(a, b, k):
    while a * a > k:
        a, b = b, a % b
    return (a, b)

def mAp5(p):
    return mAp4(p, mAp3(p), p)

def mAp6(a, b, c, d):
    yield (a * c - b * d, a * d + b * c)
    yield (a * c + b * d, a * d - b * c)

def mAp7(n):
    if n == 1:
        return [(0, 1), (0, -1), (1, 0), (-1, 0)]
    p = get_p(n)
    x, y = 1, 1
    if p % 4 == 3:
        if n % (p ** 2) != 0:
            return []
        x, y = 0, p
        p *= p
    elif p % 4 == 1:
        x, y = mAp5(p)
    new_sol = set()
    for a, b in mAp7(n // p):
        for sol in mAp6(x, y, a, b):
            new_sol.add(sol)
    return list(new_sol)

pts = (mAp7(rad))
if extra:
    for i in range(100):
        x = random.randint(2 * 10 ** 8, 10 ** 9)
        x *= random.choice([-1, 1])
        y = random.randint(2 * 10 ** 8, 10 ** 9)
        y *= random.choice([-1, 1])
        pts.append((x, y))
random.shuffle(pts)
print(len(pts), 0)
print(0, 0)
print(10**9,10**9)
for i in range(len(pts)):
    print(pts[i][0], pts[i][1])
print(5 * len(pts))
for j in range(5):
    for i in range(len(pts)):
        if not tiny:
            print(i + 1, 10000000)
        else:
            print(i + 1, 1000)

