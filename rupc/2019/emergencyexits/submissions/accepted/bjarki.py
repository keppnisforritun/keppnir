import sys
from heapq import *

n, m, k = map(int, sys.stdin.readline().strip().split())

INF = 10**100
dist = [INF]*n
Q = []

for x in map(int, sys.stdin.readline().strip().split()):
    x -= 1
    dist[x] = 0
    heappush(Q, (0, x))

adj = {}
for i in range(m):
    a, b, c = map(int, sys.stdin.readline().strip().split())
    a -= 1
    b -= 1
    if b not in adj:
        adj[b] = []
    adj[b].append((a,c))

mx = 0
cnt = 0
while Q:
    (d,cur) = heappop(Q)
    if d != dist[cur]:
        continue

    mx = d
    cnt += 1

    for (nxt,w) in adj.get(cur, []):
        nd = d + w
        if nd < dist[nxt]:
            dist[nxt] = nd
            heappush(Q, (nd, nxt))

if cnt != n:
    print('        DANGER        ')
else:
    print(mx)

