import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
sm = int(sys.argv[2])

arr = []
for i in range(n):
    mn = max(1, (sm + n-i-1) // (n-i))
    mx = min(10**9, sm)
    mx = min(mx, sm-(n-i)+1)
    cur = random.randint(mn,mx)
    arr.append(cur)
    sm -= cur

assert sm == 0

starts = set()
while len(starts) < n:
    starts.add(random.randint(1, 10**9))

ex = []
starts = list(starts)
random.shuffle(starts)
random.shuffle(arr)
sys.stdout.write('%d\n' % n)
for (x,y) in zip(starts, arr):
    sys.stdout.write('%d %d\n' % (x,y))

