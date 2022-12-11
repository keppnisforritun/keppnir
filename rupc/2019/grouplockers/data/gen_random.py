import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
m = int(sys.argv[2])

sys.stdout.write('%d %d\n' % (n, m))
print(''.join(map(str, [ random.randint(0, 4) for _ in range(m) ])))

