#!/usr/bin/python3
import sys
import random

random.seed(int(sys.argv[-1]))

typ = sys.argv[1]

if typ == "max":
    print("1 sinni daglega")
    print("10 ar")
    print("1 sekunda")

if typ == "zero":
    print("1 sinni arlega")
    print("1 sekunda")
    print("5 sekundur")

if typ == "negone":
    print("1 sinni arlega")
    print("1 sekunda")
    print("6 sekundur")
