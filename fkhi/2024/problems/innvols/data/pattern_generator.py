#!/usr/bin/python3
import sys, random, math
random.seed(int(sys.argv[-1]))

min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
pattern = sys.argv[3]

n = random.randint(min_n, max_n)
content = []
for i in range(n):
    content.append(pattern[i % len(pattern)])
print(''.join(content))
