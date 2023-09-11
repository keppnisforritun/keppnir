import math

g = []
def solve(inps, outs, f):
    if len(inps) == 0:
        return
    if len(inps) == len(outs):
        for i in range(len(inps)):
            g[inps[i]].append(outs[i])
        return
    if len(inps) == 1:
        root = inps[0]
        k = (len(outs) - 1).bit_length()
        lft = 2 ** k - len(outs)
        for i in range(k):
            new_inp = []
            for j in range(len(inps)):
                y = len(g)
                g.append([])
                g[inps[j]].append(y)
                new_inp.append(y)
                if lft >= 2 ** (k - i - 1):
                    g[inps[j]].append(root)
                    lft -= 2 ** (k - i - 1)
                else:
                    g.append([])
                    g[inps[j]].append(y + 1)
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
            g[inps[-1]].append(outs[i])
            inps.pop()
        solve(inps, outs, f)
        return
    if f <= len(inps).bit_length():
        new_inp = []
        for x in inps:
            y = len(g)
            g.append([])
            g.append([])
            g[x].append(y)
            g[x].append(y + 1)
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
            g.append([])
            g[inps[i]].append(y)
            g[inps[i + 1]].append(y)
            new_inp.append(y)
        inps = new_inp
    return 

def fix_indeg(g):
    ins = [[] for i in range(len(g))]
    for i in range(len(g)):
        for j in g[i]:
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
    h = [[] for i in range(len(ins))]
    for i in range(len(ins)):
        for j in ins[i]:
            h[j].append(i)
    return h

def filter_single(g):
    ind2ind = dict()
    grev = [[] for i in range(len(g))]
    for i in range(len(g)):
        for j in g[i]:
            grev[j].append(i)
    for i in range(len(g)):
        if len(grev[i]) == 1 and len(g[i]) == 1:
            continue
        x = len(ind2ind)
        ind2ind[i] = x
    newg = [[] for i in range(len(ind2ind))]
    for i in range(len(g)):
        if i in ind2ind:
            for j in g[i]:
                if j in ind2ind:
                    newg[ind2ind[i]].append(ind2ind[j])
        else:
            newg[ind2ind[grev[i][0]]].append(ind2ind[g[i][0]])
    return newg

n, m = map(int, input().strip().split())
for i in range(n + m):
    g.append([])
com = math.gcd(n, m)
solve(list(range(n)), list(range(n, n + m)), 1)
g = fix_indeg(g)
g = filter_single(g)

ecnt = 0
for i in range(len(g)):
    ecnt += len(g[i])

extra = min(50000 - len(g), 50000 - ecnt - 1)

pick = -1
print(len(g) + extra, ecnt + extra + 1)
for i in range(len(g)):
    for j in g[i]:
        if pick == -1:
            print(i + 1, len(g) + 1)
            print(len(g) + 1, j + 1)
            pick = len(g) + 1
        else:
            print(i + 1, j + 1)
for i in range(len(g) + 1, len(g) + extra):
    print(i, i + 1)
print(len(g) + extra, len(g) + 1)
