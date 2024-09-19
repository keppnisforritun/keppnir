#!/usr/bin/python3
import sys

if __name__ == "__main__":
    n = int(sys.stdin.readline())
    degs = list(map(int, sys.stdin.readline().split()))
    # Edge case, constant time
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
    # Linear time pass
    sm = 0
    for i in range(n):
        if degs[i] <= 0 or degs[i] >= n:
            print("Omogulegt!")
            exit(0)
        sm += degs[i]
    # Known necessary conditions
    if sm % 2 != 0 or sm < 2 * (n - 1):
        print("Omogulegt!")
        exit(0)
    # count[i] contains indices of vertices
    # with degree i unassigned
    count = [[] for _ in range(n)]
    for i in range(len(degs)):
        count[degs[i]].append(i)
    # nxt[i] contains next lower index with
    # nonzero count[i].len(), can be imagined
    # as a linked list, except each entry has
    # the index of the next entry
    nxt = [i - 1 for i in range(n)]
    edges = []
    # lo points to lowest degree, hi to highest
    lo, hi = 0, n - 1
    while lo <= hi:
        # amortized ok
        while lo < n and len(count[lo]) == 0:
            lo += 1
        if lo == n:
            break
        cur = count[lo][-1]
        count[lo].pop()
        left = lo
        # mov contains vertices used in this iteration
        # that are to be added back afterwards
        # cut contains degrees that are now empty,
        # to be augmented so they can be skipped next time
        mov, cut = [], []
        old_hi = hi
        # now we match lo many vertices
        while left > 0:
            # high degree lowered using nxt
            while hi > 0 and len(count[hi]) == 0:
                # empty entries noted for possible deletion
                if len(count[nxt[hi]]) == 0:
                    cut.append(hi)
                hi = nxt[hi]
            # if we run out, it's impossible
            if hi == 0:
                print("Omogulegt!")
                exit(0)
            neigh = count[hi][-1]
            count[hi].pop()
            edges.append((cur, neigh))
            if hi != 1:
                # to be added to another degree post iteration
                mov.append((hi - 1, neigh))
            left -= 1
        for (ind, vert) in mov:
            count[ind].append(vert)
            # we must have visited ind + 1 this iteration,
            # so this insertion works
            if nxt[ind + 1] != ind:
                nxt[ind] = nxt[ind + 1]
                nxt[ind + 1] = ind
            # may increase hi a lot, but by the end of this iteration
            # nxt will make sure we only visit 
            hi = max(hi, ind)
            # can only lower lo by 1, so still linear steps
            lo = min(lo, ind)
        for ind in cut:
            if len(count[nxt[ind]]) == 0:
                # ind is removed from nxt chain
                # hi is updated too if it was there so it remains
                # at a valid index in the chain
                if hi == nxt[ind]:
                    hi = nxt[nxt[ind]]
                nxt[ind] = nxt[nxt[ind]]
        # linear in length of cut
        # now nxt chain contains only nonempty
    if sm // 2 != len(edges):
        print("Omogulegt!")
        exit(0)
    print(n, len(edges))
    for a, b in edges:
        print(a + 1, b + 1)
