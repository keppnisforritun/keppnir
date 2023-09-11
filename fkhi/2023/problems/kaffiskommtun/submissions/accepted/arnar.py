import sys
import bisect

n, c, t = map(int, sys.stdin.readline().split())
ts = list(map(int, sys.stdin.readline().split()))

dp = [0 for i in range(n + 1)]
for i in range(n - 1, -1, -1):
    lo, hi = i+1, n-1
    j = n
    while lo <= hi:
        mid = (lo+hi)//2
        if ts[mid] < ts[i]+t:
            lo = mid+1
        else:
            hi = mid-1
            j = mid
    for k in range(j, min(j + c, n)):
        dp[i] = max(dp[i], k - j + dp[k] + 1)

print(max(dp))
