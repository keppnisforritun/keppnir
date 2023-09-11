import bisect

n, c, t = map(int, input().strip().split())
ts = list(map(int, input().strip().split()))

dp = [0 for i in range(n + 1)]
for i in range(n - 1, -1, -1):
    j = bisect.bisect_left(ts, ts[i] + t, i+1)
    for k in range(j, min(j + c, n)):
        dp[i] = max(dp[i], k - j + dp[k] + 1)

print(max(dp))
