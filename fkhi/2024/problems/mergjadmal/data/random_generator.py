#!/usr/bin/python3
import sys
import random
import string

random.seed(int(sys.argv[-1]))
opts = list(string.printable)
for c in string.whitespace:
    del opts[opts.index(c)]

outp = []
for _ in range(999):
    outp.append(random.choice(opts))

if random.randint(1, 2) == 1:
    if random.randint(1, 2) == 1:
        x = random.randint(0, 997)
        outp[x] = '6'
        outp[x + 1] = '9'
    else:
        x = random.randint(0, 996)
        outp[x] = '4'
        outp[x + 1] = '2'
        outp[x + 2] = '0'

sys.stdout.write("".join(outp) + "\n")
