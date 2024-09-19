#!/usr/bin/python3
import sys, math

n = int(sys.stdin.readline())
xs = sorted(list(map(float, sys.stdin.readline().strip().split())))

for _ in range(10 ** 4):
    xs = [
        sum(xs) / len(xs),
        math.exp(sum([math.log(x) for x in xs]) / len(xs)),
        sorted(xs)[len(xs) // 2]
    ]

print("{:.4f}".format(xs[0]))
