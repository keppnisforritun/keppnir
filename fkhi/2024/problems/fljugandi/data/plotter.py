#!/usr/bin/python3
import matplotlib.pyplot as plt
import math

import sys

limit = math.inf

if len(sys.argv) >= 2:
    limit = int(sys.argv[1])

n, h = map(int, input().strip().split())
st = tuple(map(int, input().strip().split()))
nd = tuple(map(int, input().strip().split()))
locs = [tuple(map(int, input().strip().split())) for _ in range(n)]
m = int(input())
upd = [tuple(map(int, input().strip().split())) for _ in range(m)]

mnx, mxx = 0, 0
mny, mxy = 0, 0

for i in range(len(upd)):
    x = locs[upd[i][0] - 1][0]
    y = locs[upd[i][0] - 1][1]
    r = upd[i][1]
    mnx = min(mnx, x - r)
    mxx = max(mxx, x + r)
    mny = min(mny, y - r)
    mxy = max(mxy, y + r)

fig, ax = plt.subplots()

mn = min(mnx, mny)
mx = max(mxx, mxy)

ax.set_xlim((mn, mx))
ax.set_ylim((mn, mx))

rads = [0 for i in range(n)]

for i in range(min(len(upd), limit)):
    rads[upd[i][0] - 1] = max(rads[upd[i][0] - 1], upd[i][1])

for i in range(n):
    x = locs[i][0]
    y = locs[i][1]
    r = rads[i]
    if r <= h:
        continue
    r = math.sqrt(r * r - h * h)
    print(x, y, x**2+y**2-r**2)
    circle = plt.Circle((x, y), r, color='blue')
    plt.text(x, y, str(i), fontsize=12)
    ax.add_patch(circle)

plt.plot(*st, 'go')
plt.plot(*nd, 'ro')
plt.text(st[0] * 1.01, st[1] * 1.01, "s", fontsize=12)
plt.text(nd[0] * 0.99, nd[1] * 0.99, "t", fontsize=12)

fig.savefig('plt.png')
plt.show()
