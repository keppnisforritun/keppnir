#!/usr/bin/python3
import sys

inp = sys.stdin.readline()
assert 1 <= len(inp) <= 1000
assert inp.isascii()
assert inp.strip().isprintable()
assert ' ' not in inp
assert not sys.stdin.readline()

sys.exit(42)
