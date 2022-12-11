import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
m = int(sys.argv[2])

sys.stdout.write('%d %d\n' % (n, m))

