import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
small_len = int(sys.argv[2])
last_len = int(sys.argv[3])

sys.stdout.write('%d\n' % (n+1))

seen = set()
seen.add(10**9)
ex = [(10**9, last_len)]

for i in range(n):
    while True:
        start = random.randint(10**7, 10**9)
        if start not in seen and start-1 not in seen:
            break
    seen.add(start)
    ex.append((start, small_len))

random.shuffle(ex)
for (u,v) in ex:
    sys.stdout.write('%d %d\n' % (u,v))

