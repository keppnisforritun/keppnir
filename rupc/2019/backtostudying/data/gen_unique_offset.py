import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
shift = int(sys.argv[2])

starts = set()
while len(starts) < n:
    x = random.randint(1, 10**9)
    if x-1 not in starts and x+1 not in starts:
        starts.add(x)

starts = sorted(starts)

sys.stdout.write('%d\n' % n)
ex = []
last = -1
for x in starts:
    ex.append((x, x - last - 1))
    last = x

i = random.randint(0,n-1)
ex[i] = (ex[i][0], ex[i][1] + shift)

random.shuffle(ex)
for (u,v) in ex:
    sys.stdout.write('%d %d\n' % (u,v))

