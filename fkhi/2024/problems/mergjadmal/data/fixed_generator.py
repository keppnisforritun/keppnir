#!/usr/bin/python3
import sys
import string

opts = list(string.printable)
for c in string.whitespace:
    del opts[opts.index(c)]

ind = int(sys.argv[1])
sys.stdout.write([
    "69",
    "420",
    "620",
    "29",
    "69420",
    "".join(opts),
    string.punctuation,
    "",
][ind] + "\n")
