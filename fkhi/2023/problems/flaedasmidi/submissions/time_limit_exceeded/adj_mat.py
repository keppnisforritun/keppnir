import math

def extend(g):
    for i in range(len(g)):
        g[i].append(0)
    g.append([0 for i in range(len(g[0]))])

g = []
def solve(inps, outs, f):
    if len(inps) == 0:
        return
    if len(inps) == len(outs):
        for i in range(len(inps)):
            g[inps[i]][outs[i]] = 1
        return
    if len(inps) == 1:
        root = inps[0]
        k = (len(outs) - 1).bit_length()
        lft = 2 ** k - len(outs)
        for i in range(k):
            new_inp = []
            for j in range(len(inps)):
                y = len(g)
                extend(g)
                g[inps[j]][y] = 1
                new_inp.append(y)
                if lft >= 2 ** (k - i - 1):
                    g[inps[j]][root] = 1
                    lft -= 2 ** (k - i - 1)
                else:
                    extend(g)
                    g[inps[j]][y + 1] = 1
                    new_inp.append(y + 1)
            inps = new_inp
        solve(inps, outs, f)
        return
    com = math.gcd(len(inps), len(outs))
    if com > 1:
        for i in range(com):
            solve(inps[i::com], outs[i::com], f)
        return
    if len(inps) >= len(outs):
        for i in range(len(outs)):
            g[inps[-1]][outs[i]] = 1
            inps.pop()
        solve(inps, outs, f)
        return
    if f <= len(inps).bit_length():
        new_inp = []
        for x in inps:
            y = len(g)
            extend(g)
            extend(g)
            g[x][y] = 1
            g[x][y + 1] = 1
            new_inp.append(y)
            new_inp.append(y + 1)
        solve(new_inp, outs, f + 1)
        return
    while len(inps) > 0:
        if len(inps) % 2 == 1:
            solve([inps[-1]], outs, f)
            inps.pop()
        new_inp = []
        for i in range(0, len(inps), 2):
            y = len(g)
            extend(g)
            g[inps[i]][y] = 1
            g[inps[i + 1]][y] = 1
            new_inp.append(y)
        inps = new_inp
    return 

def fix_indeg(g):
    ins = [[] for i in range(len(g))]
    for i in range(len(g)):
        for j in range(len(g)):
            if g[i][j]:
                ins[j].append(i)
    mx = len(ins)
    for i in range(mx):
        while len(ins[i]) > 2:
            x = len(ins)
            ins.append([])
            ins[-1].append(ins[i][-1])
            ins[i].pop()
            ins[-1].append(ins[i][-1])
            ins[i].pop()
            ins[i].append(x)
    h = [[0 for j in range(len(ins))] for i in range(len(ins))]
    for i in range(len(ins)):
        for j in ins[i]:
            h[j][i] = 1
    return h

def filter_single(g):
    ind2ind = dict()
    grev = [[] for i in range(len(g))]
    gfwd = [[] for i in range(len(g))]
    for i in range(len(g)):
        for j in range(len(g)):
            if g[i][j]:
                grev[j].append(i)
                gfwd[i].append(j)
    for i in range(len(g)):
        if len(grev[i]) == 1 and len(gfwd[i]) == 1:
            continue
        x = len(ind2ind)
        ind2ind[i] = x
    newg = [[0 for j in range(len(ind2ind))] for i in range(len(ind2ind))]
    for i in range(len(g)):
        if i in ind2ind:
            for j in range(len(g)):
                if g[i][j]:
                    if j in ind2ind:
                        newg[ind2ind[i]][ind2ind[j]] = 1
        else:
            newg[ind2ind[grev[i][0]]][ind2ind[gfwd[i][0]]] = 1
    return newg

n, m = map(int, input().strip().split())
g = [[0 for i in range(n + m)] for j in range(n + m)]
com = math.gcd(n, m)
solve(list(range(n)), list(range(n, n + m)), 1)
g = fix_indeg(g)
g = filter_single(g)

ecnt = 0
for i in range(len(g)):
    ecnt += sum(g[i])
print(len(g), ecnt)
for i in range(len(g)):
    for j in range(len(g)):
        if g[i][j]:
            print(i + 1, j + 1)
