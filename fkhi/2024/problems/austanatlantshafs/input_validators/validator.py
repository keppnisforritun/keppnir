#!/usr/bin/python3

import sys

n = int(input())
dat = [list(input().strip().split()) for _ in range(n)]
ind = dict()
for i in range(n):
    ind[dat[i][0]] = i
is_par = [False for _ in range(n)]
for i in range(1, n):
    is_par[ind[dat[i][1]]] = True
for i in range(n):
    assert is_par[i] == (dat[i][2] == "-1")

sys.exit(42)

