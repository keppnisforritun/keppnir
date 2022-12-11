import math
import sys

n = int(sys.stdin.readline())
res = 0
for i in range(n):
    deg, r1, r2 = map(int, sys.stdin.readline().split())
    if r1 == r2:
        continue
    res += (deg / 360.0) * (math.pi) * r2 * r2
    res -= (deg / 360.0) * (math.pi) * r1 * r1

print('%0.10f' % res)

