import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
max_len = int(sys.argv[2])
bound_lower = sys.argv[3] == 'true'

sys.stdout.write('%d\n' % (n))
seen = set()
for i in range(n):
    while True:
        start = random.randint(1,10**9)
        if start not in seen:
            break
    seen.add(start)
    sys.stdout.write('%d %d\n' % (start, random.randint(1, min(max_len, start) if bound_lower else max_len)))

