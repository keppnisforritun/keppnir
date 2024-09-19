#!/usr/bin/python3
import sys, itertools

l = int(sys.stdin.readline())
mx, opts = [], []
for _ in range(l):
    dat = list(sys.stdin.readline().strip().split())[1:]
    mx.append(len(dat))
    opts.append(sorted(dat))

out = 0
for inds in itertools.product(*[range(x) for x in mx]):
    for i in range(len(inds)):
        out += len(opts[i][inds[i]])

assert out <= 10 ** 6

sys.exit(42)
