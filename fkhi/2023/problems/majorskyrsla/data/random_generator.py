import random
import sys

random.seed(sys.argv[-1])

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
min_k = int(sys.argv[3])
max_k = int(sys.argv[4])

n = random.randint(min_n, max_n)
k = random.randint(min_k, max_k)
while n * (n - 1) // 2 < k:
    k = random.randint(min_k, max_k)
print(n, k)
