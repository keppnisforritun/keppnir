#!/usr/bin/python3
import sys, random, math
random.seed(int(sys.argv[-1]))

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])

chars = "ACGT"

n = random.randint(min_n, max_n)
content = random.choices(chars, k=n)
print(''.join(content))
