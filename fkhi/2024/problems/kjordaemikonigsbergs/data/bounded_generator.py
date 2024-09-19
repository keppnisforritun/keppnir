#!/usr/bin/python3
import sys
import random

random.seed(int(sys.argv[-1]))

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
min_m = int(sys.argv[3])
max_m = int(sys.argv[4])
min_d = int(sys.argv[5])
max_d = int(sys.argv[6])

assert min_n <= max_n
assert min_m <= max_m

n = random.randint(min_n, max_n)

max_d = min(max_d, n - 1)

k = 3
from_sequence = [min(random.randint(min_d, max_d) for i in range(k)) for _ in range(n)]
to_sequence = from_sequence

m = sum(from_sequence) // 2
while m > max_m:
    a = random.randint(0, n-1)
    b = random.randint(0, n-1)
    if a == b:
        continue
    change = random.randint(0, min(from_sequence[a], to_sequence[b]) - min_d)
    from_sequence[a] -= change
    to_sequence[b] -= change
    m -= change

while m < min_m:
    a = random.randint(0, n-1)
    b = random.randint(0, n-1)
    if a == b or from_sequence[a] >= max_d or to_sequence[b] >= max_d:
        continue
    change = 1
    from_sequence[a] += change
    to_sequence[b] += change
    m += change

sys.stdout.write(f"{n}\n")
sys.stdout.write(f"{' '.join(map(str, from_sequence))}\n")
