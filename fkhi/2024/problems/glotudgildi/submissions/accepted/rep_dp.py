#!/usr/bin/python3
import functools
import sys
import itertools

@functools.cache
def binom(n, m):
    if n < 0 or m < 0 or m > n:
        return 0
    if n == m or m == 0:
        return 1
    return binom(n - 1, m) + binom(n - 1, m - 1)

def landau(v):
    n = len(v)
    if v[0] < 0:
        return False
    if v[-1] >= n:
        return False
    sm = 0
    for i in range(n - 1):
        sm += v[i]
        if sm < i * (i + 1) // 2:
            return False
    sm += v[-1]
    return sm == n * (n - 1) // 2

def pred_gen(mx, sm):
    sufmx = mx[:]
    for i in range(len(sufmx) - 2, -1, -1):
        sufmx[i] += sufmx[i + 1]
    cur = [0 for _ in range(len(mx) + 1)]
    stk = [(sm, 0, -1)]
    while len(stk) > 0:
        left, i, x = stk[-1]
        stk.pop()
        if i == len(mx):
            if left == 0:
                yield cur
            continue
        cur_mn = max(0, left - sufmx[i])
        x = max(x, cur_mn)
        cur_mx = min(mx[i], left)
        if x > cur_mx:
            continue
        cur[i] = x
        stk.append((left, i, x + 1))
        stk.append((left - x, i + 1, -1))

@functools.cache
def dp(v):
    n = len(v)
    if v == ():
        return 1
    if v[0] < 0 or v[-1] >= n:
        return 0
    if v[-1] == n - 1:
        return dp(v[:-1])
    if n - 1 - v[-1] > v[0]:
        return dp(tuple(n - 1 - x for x in v[::-1]))
    rep = [0 for i in range(n)]
    for x in v:
        rep[x] += 1
    rep[v[-1]] -= 1
    m = n - 1 - v[-1]
    ans = 0
    for sub in pred_gen(rep, m):
        seq = []
        c = 1
        for i in range(len(rep)):
            c *= binom(rep[i], sub[i])
            for j in range(rep[i] - sub[i] + sub[i + 1]):
                seq.append(i)
        ans += c * dp(tuple(sorted(seq)))
    return ans

if __name__ == "__main__":
    n = int(sys.stdin.readline())
    if n == 0:
        print(1)
        exit(0)
    score = tuple(sorted(list(map(int, sys.stdin.readline().strip().split()))))
    if not landau(score):
        sys.stdout.write("0\n")
    else:
        sys.stdout.write(str(dp(score)) + "\n")
