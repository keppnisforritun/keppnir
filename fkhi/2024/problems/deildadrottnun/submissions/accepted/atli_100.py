#!/usr/bin/python3
import sys
n = int(sys.stdin.readline())
ans = []
cur = 1
while n >= cur:
    ans.append(cur)
    n -= cur
    cur += 1
for i in range(len(ans) - n, len(ans)):
    ans[i] += 1
sys.stdout.write(str(len(ans)))
sys.stdout.write("\n")
for x in ans:
    sys.stdout.write(str(x))
    sys.stdout.write(" ")
sys.stdout.write("\n")
