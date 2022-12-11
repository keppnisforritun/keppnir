import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
m = int(sys.argv[2])
k = int(sys.argv[3])
back = sys.argv[4] == 'true'

es = set()
for i in range(n-1):
    es.add((i+1,i+2))

while len(es) < m:
    a = random.randint(1,n)
    b = random.randint(1,n)
    if a != b:
        if back or a < b:
            es.add((a,b))

sys.stdout.write('%d %d %d\n' % (n, len(es), k))

used = set()
for i in range(k):
    while True:
        x = random.randint(1,n)
        if i == 0:
            x = n
        if x not in used:
            break
    used.add(x)
    if i != 0:
        sys.stdout.write(' ')
    sys.stdout.write('%d' % x)
sys.stdout.write('\n')

es = list(es)
random.shuffle(es)
for (a,b) in es:
    sys.stdout.write('%d %d %d\n' % (a, b, random.randint(0,10**6)))

