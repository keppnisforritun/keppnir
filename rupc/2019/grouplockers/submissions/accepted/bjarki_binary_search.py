import sys

n, m = map(int, sys.stdin.readline().strip().split())
arr = list(map(int, sys.stdin.readline().strip()))
pre = []
for i in range(len(arr)):
    cur = arr[i]
    if i > 0:
        cur += pre[-1]
    pre.append(cur)

best = 10000000000
for i in range(m):
    lo = 1
    hi = m-i

    while lo <= hi:
        mid = (lo+hi)//2
        j = i + mid - 1
        assert j < m
        cur = pre[j]
        if i > 0:
            cur -= pre[i-1]
        if cur >= n:
            best = min(best, mid)
            hi = mid-1
        else:
            lo = mid+1

if best == 10000000000:
    print('     \n\n      IMPOSSIBLE    \n       ')
else:
    print(best-1)

