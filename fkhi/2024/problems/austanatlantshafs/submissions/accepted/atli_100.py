#!/usr/bin/python3
import sys

if __name__ == "__main__":
    n = int(sys.stdin.readline())
    xs, names, par = [], [], []
    ch = [[] for _ in range(n)]
    ind = dict()
    for i in range(n):
        s, t, x = sys.stdin.readline().strip().split()
        xs.append(int(x))
        names.append(s)
        ind[s] = i
        par.append(t)
    for i in range(1, n):
        ch[ind[par[i]]].append(i)
    ans = [0 for _ in range(n)]
    mxes = [(-1, -1) for _ in range(n)]
    stk = [0]
    while len(stk) > 0:
        cur = stk[-1]
        if len(ch[cur]) == 0:
            ans[cur] = cur
            mxes[cur] = (xs[cur], cur)
            stk.pop()
            continue
        if mxes[ch[cur][0]] == (-1, -1):
            for y in ch[cur]:
                stk.append(y)
            continue
        for y in ch[cur]:
            if mxes[y][0] > mxes[cur][0]:
                mxes[cur] = mxes[y]
            elif mxes[y][0] == mxes[cur][0]:
                mxes[cur] = (mxes[cur][0], -1)
        if mxes[cur][1] != -1:
            ans[mxes[cur][1]] = cur
        stk.pop()
    for i in range(n):
        if xs[i] == -1:
            continue
        sys.stdout.write(names[ans[i]])
        sys.stdout.write("\n")
