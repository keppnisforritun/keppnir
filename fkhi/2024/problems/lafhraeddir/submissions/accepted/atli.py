#!/usr/bin/python3
import sys

class FlowNetwork:
    def __init__(self, n):
        self.n = n
        self.curh = [-1 for _ in range(self.n)]
        self.head = [-1 for _ in range(self.n)]
        self.q = [-1 for _ in range(2000)]
        self.d = []
        self.e_v = []
        self.e_nxt = []
        self.e_cap = []
        self.e_store = []
    def reset(self):
        self.e_cap = self.e_store[:]
    def add_edge(self, u, v, uv, vu = 0):
        self.e_v.append(v)
        self.e_nxt.append(self.head[u])
        self.e_cap.append(uv)
        self.head[u] = len(self.e_v) - 1
        self.e_v.append(u)
        self.e_nxt.append(self.head[v])
        self.e_cap.append(vu)
        self.head[v] = len(self.e_v) - 1
    def augment(self, v, t, f):
        if v == t:
            return f
        while self.curh[v] != -1:
            if self.e_cap[self.curh[v]] > 0 and self.d[self.e_v[self.curh[v]]] + 1 == self.d[v]:
                ret = self.augment(self.e_v[self.curh[v]], t, min(f, self.e_cap[self.curh[v]]))
                if ret > 0:
                    self.e_cap[self.curh[v]] -= ret
                    self.e_cap[self.curh[v] ^ 1] += ret
                    return ret
            self.curh[v] = self.e_nxt[self.curh[v]]
        return 0
    def max_flow(self, s, t):
        self.e_store = self.e_cap[:]
        l, r, f, x = 0, 0, 0, 0
        while True:
            self.d = [-1 for _ in range(self.n)]
            l, r = 0, 0
            self.q[r] = t
            r += 1
            self.d[t] = 0
            while l < r:
                v = self.q[l]
                i = self.head[v]
                l += 1
                while i != -1:
                    if self.e_cap[i ^ 1] > 0 and self.d[self.e_v[i]] == -1:
                        self.q[r] = self.e_v[i]
                        r += 1
                        self.d[self.e_v[i]] = self.d[v] + 1
                    i = self.e_nxt[i]
            if self.d[s] == -1:
                break
            self.curh = self.head[:]
            while True:
                x = self.augment(s, t, 2 ** 60)
                if x == 0:
                    break
                f += x
        self.reset()
        return f

if __name__ == "__main__":
    L, E = map(int, sys.stdin.readline().strip().split())
    aind = dict()
    aname, dname, acnt, astr, dcnt, dstr = [], [], [], [], [], []
    immune = [[0 for _ in range(E)] for _ in range(L)]
    for i in range(E):
        nam, st, cn = sys.stdin.readline().strip().split()
        aname.append(nam)
        astr.append(int(st))
        acnt.append(int(cn))
        aind[aname[i]] = i
    for i in range(L):
        data = sys.stdin.readline().strip().split()
        dname.append(data[0])
        dstr.append(int(data[1]))
        dcnt.append(int(data[2]))
        for imm in data[4:]:
            immune[i][aind[imm]] = 1
    fw = FlowNetwork(E + L + 2)
    edits = []
    for i in range(E):
        fw.add_edge(E + L, i, acnt[i])
    for i in range(L):
        for j in range(E):
            if immune[i][j]:
                continue
            if astr[j] < dstr[i]:
                continue
            fw.add_edge(j, E + i, 2 ** 60)
    for i in range(L):
        edits.append((len(fw.e_cap), dcnt[i]))
        fw.add_edge(E + i, E + L + 1, 0)
    lo, hi = 0, 10 ** 12
    while hi > lo:
        md = hi - (hi - lo) // 2
        targ = 0
        for i in range(L):
            fw.e_cap[edits[i][0]] = md * edits[i][1]
            targ += md * edits[i][1]
        if targ > 10 ** 9 * E:
            hi = md - 1
            continue
        if fw.max_flow(E + L, E + L + 1) < targ:
            hi = md - 1
        else:
            lo = md
    sys.stdout.write(str(lo))
    sys.stdout.write("\n")
        
