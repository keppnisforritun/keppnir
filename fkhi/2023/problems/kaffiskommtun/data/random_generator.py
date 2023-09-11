import random
import sys

random.seed(sys.argv[-1])

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
max_c = int(sys.argv[3])
max_t = int(sys.argv[4])

n = random.randint(min_n, max_n)
c = random.randint(1, max_c)
t = random.randint(max(1, max_t // 2), max_t)

ti = [random.randint(1, 20)]

for i in range(n - 1):
    if random.randint(1, 2) == 1:
        ti.append(ti[-1] + random.randint(0, 5))
    else:
        ti.append(ti[-1] + random.randint(1, 100))

print(n, c, t)
print(" ".join([str(x) for x in ti]))
