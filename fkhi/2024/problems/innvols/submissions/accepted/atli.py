#!/usr/bin/python3
import sys, collections

dna = sys.stdin.readline().strip()
res = collections.Counter()

for i in range(len(dna)):
    for j in range(i, len(dna)):
        res[dna[i:j+1]] += 1

for (k, v) in sorted([(-v, k) for (k, v) in res.items()]):
    sys.stdout.write(f"{-k} {v}\n")

