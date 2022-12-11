import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
m = int(sys.argv[2])

sm = 360
deg = []
for i in range(n):
    mn = 1
    mx = sm - (n-i-1)

    if i == n-1:
        mn = sm

    cur = random.randint(mn,mx)
    deg.append(cur)
    sm -= cur

assert sm == 0

random.shuffle(deg)

skip = set()
while len(skip) < m:
    skip.add(random.randint(0,n-1))

sys.stdout.write('%d\n' % (n))
for i,d in enumerate(deg):
    if i in skip:
        sys.stdout.write('%d %d %d\n' % (d, 0, 0))
    else:
        while True:
            r1 = random.randint(0, 1000)
            r2 = random.randint(0, 1000)
            if r1 < r2:
                break
        sys.stdout.write('%d %d %d\n' % (d, r1, r2))

