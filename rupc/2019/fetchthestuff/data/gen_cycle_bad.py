import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
m = int(sys.argv[2])
k = int(sys.argv[3])

assert n >= 5
assert k >= 2

used = set()
def vertex():
    while True:
        x = random.randint(1,n)
        if x not in used:
            used.add(x)
            return x

end = n
used.add(end)
A = vertex()
B = vertex()

es = []
arr = [ vertex() for _ in range(n-3) ]
for i in range(n-3):
    j = (i+1) % len(arr)
    es.append((arr[i], arr[j], 'locked'))

t = random.randint(0, len(arr)-1)
es.append((arr[t],A,'locked'))
es.append((A,end,'locked'))
t = random.randint(0, len(arr)-1)
es.append((arr[t],B,'locked'))
es.append((B,end,'locked'))

while len(es) < m:
    u = random.randint(0,len(arr)-1)
    v = random.randint(0,len(arr)-1)
    if u != v:
        es.append((arr[u],arr[v],random.choice(['open', 'locked'])))

items = [ i for i in range(2,n) if i not in [A,B] ]
random.shuffle(items)
items = [A,B] + items[:k-2]
random.shuffle(items)

assert len(used) == n
assert len(items) == k
print('%d %d %d' % (n, len(es), len(items)))
print(' '.join(map(str, items)))
random.shuffle(es)
for (a,b,c) in es:
    print('%d %d %s' % (a,b,c))

