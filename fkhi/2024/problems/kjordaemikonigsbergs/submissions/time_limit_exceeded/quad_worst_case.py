#!/usr/bin/python3
import sys

if __name__ == "__main__":
    n = int(sys.stdin.readline())
    degs = list(map(int, sys.stdin.readline().split()))
    if n == 1:
        if degs == [0]:
            print("1 0")
        else:
            print("Omogulegt!")
        exit(0)
        if n == 1:
            if degs == [0]:
                print("1 0")
            else:
                print("Omogulegt!")
            exit(0)
    if min(degs) <= 0 or max(degs) >= n:
        print("Omogulegt!")
        exit(0)
    sm = sum(degs)
    if sm % 2 != 0 or sm < 2 * (n - 1):
        print("Omogulegt!")
        exit(0)
    count = [[] for _ in range(n)]
    for i in range(len(degs)):
        count[degs[i]].append(i)
    edges = []
    lo, hi = 0, n - 1
    while lo <= hi:
        while lo < n and len(count[lo]) == 0:
            lo += 1
        if lo == n:
            break
        cur = count[lo][-1]
        count[lo].pop()
        left = lo
        mov = []
        while left > 0:
            while hi > 0 and len(count[hi]) == 0:
                hi -= 1
            if hi == 0:
                print("Omogulegt!")
                exit(0)
            neigh = count[hi][-1]
            count[hi].pop()
            edges.append((cur, neigh))
            if hi != 1:
                mov.append((hi - 1, neigh))
            left -= 1
        for (ind, vert) in mov:
            count[ind].append(vert)
            hi = max(hi, ind)
            lo = min(lo, ind)
    if sm // 2 != len(edges):
        print("Omogulegt!")
        exit(0)
    print(n, len(edges))
    for a, b in edges:
        print(a + 1, b + 1)
