import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
k = int(sys.argv[2])

t = (n - 2) // k
vertices = 2 + t * k
es = []
start = 1
end = vertices

used = set([start,end])
items = []

def vertex():
    while True:
        x = random.randint(1,vertices)
        if x not in used:
            used.add(x)
            return x

es.append((start, end, 'open'))

for i in range(k):
    last = start
    for j in range(t):
        cur = vertex()
        es.append((last, cur, 'open'))
        last = cur
    items.append(last)

assert len(items) == k

print('%d %d %d' % (vertices, len(es), len(items)))
random.shuffle(items)
print(' '.join(map(str, items)))
random.shuffle(es)
for (a,b,c) in es:
    print('%d %d %s' % (a,b,c))

