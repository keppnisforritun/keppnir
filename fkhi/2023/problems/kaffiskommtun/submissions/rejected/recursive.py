import bisect
import sys
sys.setrecursionlimit(10**6 + 2000)

n, c, t = map(int, input().strip().split())
ts = list(map(int, input().strip().split()))

dp = [-1 for i in range(n + 1)]
dp[n] = 0
def f(i):
    global dp, ts, n, c, t
    if dp[i] == -1:
        j = bisect.bisect_left(ts, ts[i] + t)
        dp[i] = 0
        for k in range(j, min(j + c, n)):
            dp[i] = max(dp[i], k - j + f(k) + 1)
    return dp[i]

print(max(f(i) for i in range(n+1)))
