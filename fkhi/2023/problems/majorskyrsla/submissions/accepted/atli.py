n, k = map(int, input().strip().split())
desc = [False for i in range(n)]
for i in range(n - 2, -1, -1):
    if k >= i + 1:
        desc[i] = True
        k -= i + 1
mn, mx = 1, n
res = []
for i in range(n):
    if desc[i]:
        res.append(mx)
        mx -= 1
    else:
        res.append(mn)
        mn += 1
print(" ".join([str(x) for x in res]))
