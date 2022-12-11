import sys

sys.stdin.readline()

L = sum(map(int, sys.stdin.readline().strip().split()))
R = sum(map(int, sys.stdin.readline().strip().split()))

if L == R:
    sys.stdout.write('either\n')
if L < R:
    sys.stdout.write('left\n')
if R < L:
    sys.stdout.write('right\n')

