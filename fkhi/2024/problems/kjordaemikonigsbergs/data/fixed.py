#!/usr/bin/python3
import sys
import random

n, *sequence, seed = map(int, sys.argv[1:])
random.seed(seed)

sys.stdout.write(f"{n}\n")
sys.stdout.write(f"{' '.join(map(str, sequence))}\n")
