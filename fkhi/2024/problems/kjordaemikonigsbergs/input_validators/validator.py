#!/usr/bin/python3
import re
import sys

max_n = 100_000
max_m = 1_000_000

line = sys.stdin.readline()
assert re.match("^(0|[1-9][0-9]*)\n$", line)
n = int(line.rstrip('\n'))
assert 0 <= n <= max_n

line = sys.stdin.readline()
assert re.match("^((0|[1-9][0-9]*)( (0|[1-9][0-9]*))*)?\n", line)
sequence = list(map(int, line.split()))
assert len(sequence) == n
for x in sequence:
    assert 0 <= x <= max_m
assert sum(sequence) <= 2 * max_m

assert sys.stdin.read() == ''

sys.exit(42)
