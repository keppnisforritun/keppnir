import sys

sys.stdin.readline()

L = sum(map(int, sys.stdin.readline().strip().split()))
R = sum(map(int, sys.stdin.readline().strip().split()))

if L == R:
    sys.stdout.write('EITHER\n')
if L < R:
    sys.stdout.write('Left')
if R < L:
    sys.stdout.write('     \n     \n   righT      \n  \n ')

