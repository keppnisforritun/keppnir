#!/usr/bin/python3
import sys, math
from operator import mul
from functools import reduce

n = int(sys.stdin.readline())
xs = sorted(list(map(float, sys.stdin.readline().strip().split())))

for _ in range(10 ** 4):
    xs = [
        sum(xs) / len(xs),
        reduce(mul, [x ** (1 / len(xs)) for x in xs], 1),
        sorted(xs)[len(xs) // 2]
    ]

print("{:.15f}".format(xs[0]))
