#!/usr/bin/python3
import re
import sys

line = sys.stdin.readline()
assert re.match("^[ACGT]{1,100}\n$", line), "Invalid DNA sequence."

assert sys.stdin.read() == '', "Trailing input."

sys.exit(42)
