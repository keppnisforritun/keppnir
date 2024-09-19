#!/usr/bin/python3
import sys, random, math

random.seed(int(sys.argv[-1]))

typ = sys.argv[1]

if typ == "one-pass":
    print(1, 10)
    print(0, 0)
    print(0, 1)
    print(1, 0)
    print(1)
    print(1, 5)

if typ == "one-fail":
    print(1, 0)
    print(0, 0)
    print(0, 8)
    print(1, 0)
    print(1)
    print(1, 5)


