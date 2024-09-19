#!/usr/bin/python3
import re
import sys

freq = ["daglega", "vikulega", "arlega"]
plur = ["sekundur", "minutur", "klukkustundir", "dagar", "vikur", "ar"]
sing = ["sekunda", "minuta", "klukkustund", "dagur", "vika", "ar"]

line = sys.stdin.readline()
assert re.match("^[1-9][0-9]* [a-z]+ [a-z]+\n$", line)
n, wrd, frq = line.split()
n = int(n)
assert 1 <= n <= 10
if n == 1:
    assert wrd == "sinni"
else:
    assert wrd == "sinnum"
assert frq in freq

for _ in range(2):
    line = sys.stdin.readline()
    assert re.match("^[1-9][0-9]* [a-z]+", line)
    n, time = line.split()
    n = int(n)
    assert 1 <= n <= 10
    if n == 1:
        assert time in sing
    else:
        assert time in plur

assert sys.stdin.read() == ''

sys.exit(42)
