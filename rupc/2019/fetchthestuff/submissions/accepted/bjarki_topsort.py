import sys

def impossible():
    print('impossible')
    sys.exit(0)

n, m, k = map(int, sys.stdin.readline().strip().split())
items = [ int(x) for x in sys.stdin.readline().strip().split() ]

adj = [ [] for _ in range(n+1) ]
radj = [ [] for _ in range(n+1) ]
reach = [ set() for _ in range(n+1) ]
for i in range(m):
    a, b, c = sys.stdin.readline().strip().split()
    a = int(a)
    b = int(b)
    adj[a].append(b)
    radj[b].append(a)
    if c == "open":
        adj[b].append(a)
        radj[a].append(b)

for x in items + [n]:
    Q = [x]
    seen = set([ x ])
    while Q:
        cur = Q.pop()
        reach[cur].add(x)
        for nxt in radj[cur]:
            if nxt not in seen:
                seen.add(nxt)
                Q.append(nxt)

    if 1 not in seen:
        impossible()

for x in items:
    if n not in reach[x]:
        impossible()

before = [ [] for _ in range(n) ]

for x in items:
    for y in items:
        if y not in reach[x]:
            before[x].append(y)

order = []
path = set()
seen = set()
def dfs(cur):
    if cur in path:
        impossible()
    if cur in seen:
        return
    seen.add(cur)
    path.add(cur)
    for nxt in before[cur]:
        dfs(nxt)
    order.append(cur)
    path.remove(cur)

for x in items:
    dfs(x)

def transition(a,b):
    Q = [a]
    parent = { a: a }
    while Q:
        cur = Q.pop()
        for nxt in adj[cur]:
            if nxt not in parent:
                parent[nxt] = cur
                Q.append(nxt)
    assert b in parent
    res = [b]
    while res[-1] != a:
        res.append(parent[res[-1]])
    res.pop()
    while res:
        print(res.pop())

last = 1
print(last)
for x in order + [n]:
    transition(last, x)
    last = x

