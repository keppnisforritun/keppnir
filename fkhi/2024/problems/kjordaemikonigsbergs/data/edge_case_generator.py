#!/usr/bin/python3
import sys
import random

max_n = 10 ** 5
max_m = 10 ** 6
typ = sys.argv[1]
random.seed(int(sys.argv[-1]))

if typ == "count-gap":
    big = []
    for _ in range(5):
        big.append(random.randint(9 * max_n // 10, max_n))
    sm = sum(big)
    small = [5 for i in range(max_n - 5)]
    sm -= sum(small)
    while sm > 0 or sm % 2 != 0:
        x = random.randint(0, len(small) - 1)
        small[x] += 1
        sm -= 1
    degs = big + small
    random.shuffle(degs)
    print(len(degs))
    print(*degs)
