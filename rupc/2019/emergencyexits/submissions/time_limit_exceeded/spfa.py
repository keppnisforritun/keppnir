import sys
try:
    from queue import Queue
except:
    from Queue import Queue

n, m, k = map(int, sys.stdin.readline().strip().split())

INF = 10**100
dist = [INF]*n
Q = Queue()

for x in map(int, sys.stdin.readline().strip().split()):
    x -= 1
    dist[x] = 0
    Q.put((0, x))

adj = {}
for i in range(m):
    a, b, c = map(int, sys.stdin.readline().strip().split())
    a -= 1
    b -= 1
    if b not in adj:
        adj[b] = []
    adj[b].append((a,c))

while not Q.empty():
    (d,cur) = Q.get()
    if d != dist[cur]:
        continue

    for (nxt,w) in adj.get(cur, []):
        nd = d + w
        if nd < dist[nxt]:
            dist[nxt] = nd
            Q.put((nd, nxt))


mx = max(dist)
if mx == INF:
    print('danger')
else:
    print(mx)

