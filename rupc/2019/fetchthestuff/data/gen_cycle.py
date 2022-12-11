import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
m = int(sys.argv[2])
k = int(sys.argv[3])

used = set()
def vertex():
    while True:
        x = random.randint(1,n)
        if x not in used:
            used.add(x)
            return x

es = []
arr = [ vertex() for _ in range(n) ]
for i in range(n):
    j = (i+1) % n
    es.append((arr[i], arr[j], 'locked'))

while len(es) < m:
    u = random.randint(1,n)
    v = random.randint(1,n)
    if u != v:
        es.append((u,v,random.choice(['open', 'locked'])))

items = [ i for i in range(2,n) ]
random.shuffle(items)
items = items[:k]

assert len(used) == n
assert len(items) == k
print('%d %d %d' % (n, len(es), len(items)))
print(' '.join(map(str, items)))
random.shuffle(es)
for (a,b,c) in es:
    print('%d %d %s' % (a,b,c))

