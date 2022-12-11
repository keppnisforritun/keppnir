import sys
sys.setrecursionlimit(9999999)
n, m = map(int,sys.stdin.readline().strip().split())

mem = {}
def dp(a,b):
    if a < 0 or b < 0:
        return 100000000000000000000
    if a == 0 and b == 0:
        return 0
    if (a,b) in mem:
        return mem[(a,b)]

    mn = 100000000000000000000
    mn = min(mn, 249 + dp(a,b-1))
    mn = min(mn, 299 + dp(a-1,b))
    mn = min(mn, 499 + dp(a-1,b-1))
    mn = min(mn, 549 + dp(a-2,b-1))

    mem[(a,b)] = mn
    return mn

print(dp(n,m))

