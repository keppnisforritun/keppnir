n,c,t = map(int, input().split())

L = list(map(int, input().split()))

nxt = [n]*n
cur = 0
for i in range(n):
    while cur < n and L[i] + t > L[cur] :
        cur += 1
    nxt[i] = cur

dp = [[0 for i in range(c+1)] for j in range(n+1)]
for i in range(n-1, -1, -1):
    for j in range(c, 0, -1):
        dp[i][j] = 1+max(dp[i+1][j-1], dp[nxt[i]][c])
    dp[i][0] = max(dp[i][0], dp[nxt[i]][c])

print(dp[0][0])
