#!/usr/bin/python3
import sys
import random

random.seed(int(sys.argv[-1]))

freq = ["daglega", "vikulega", "arlega"]
plur = ["sekundur", "minutur", "klukkustundir", "dagar", "vikur", "ar"]
sing = ["sekunda", "minuta", "klukkustund", "dagur", "vika", "ar"]
nums = [1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9]

n1 = random.choice(nums)
wrd = "sinni" if n1 == 1 else "sinnum"
frq = random.choice(freq)
print(n1, wrd, frq)

for _ in range(2):
    ni = random.choice(nums)
    wrd = random.choice(sing if ni == 1 else plur)
    print(ni, wrd)
