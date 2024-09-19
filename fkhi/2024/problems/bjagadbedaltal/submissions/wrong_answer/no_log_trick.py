#!/usr/bin/python3
import sys
from operator import mul
from functools import reduce

n = int(sys.stdin.readline())
xs = sorted(list(map(float, sys.stdin.readline().strip().split())))

while xs[-1] - xs[0] > 1e-9:
    xs = sorted([xs[len(xs)//2], sum(xs) / len(xs), reduce(mul, xs, 1) ** (1.0 / len(xs))])

print("{:.15f}".format(xs[0]))
