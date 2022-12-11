import sys
import random

random.seed(int(sys.argv[-1]))

sys.stdout.write('%d %d\n' % (random.randint(0, 500), random.randint(0, 500)))

