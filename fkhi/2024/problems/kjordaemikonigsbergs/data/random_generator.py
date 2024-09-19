#!/usr/bin/python3
import sys
import random

random.seed(int(sys.argv[-1]))

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])

n = random.randint(min_n, max_n)
highest = random.randint(0, n-1)
sequence = [random.randint(0, highest) for _ in range(n)]
sys.stdout.write(f"{n}\n")
sys.stdout.write(f"{' '.join(map(str, sequence))}\n")
