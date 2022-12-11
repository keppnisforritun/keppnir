import sys
import random

random.seed(int(sys.argv[-1]))

MAX_N = int(sys.argv[1])
b = int(sys.argv[2])
MIN_I = -b
MAX_I = b
MAX_J = b

possible = sys.argv[3] == 'possible'

# MIN_I = -10
# MAX_I = 10
# MAX_J = 10

class UnionFind(object):
    def __init__(self, n):
        self.parent = [ i for i in range(n) ]

    def find(self, x):
        if self.parent[x] == x:
            return x
        self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, a, b):
        self.parent[self.find(a)] = self.find(b)


def get_point(i,j):
    return i*80,j*80+40

def is_valid(i,j):
    x,y = get_point(i,j)
    return x*x + y*y >= 280**2

def sees_outside(i,j):
    return i == MIN_I or i == MAX_I or j == MAX_J

def sees_inside(i,j):
    if j > 0 and not is_valid(i,j-1):
        return True
    if i < 0 and not is_valid(i+1,j):
        return True
    if i > 0 and not is_valid(i-1,j):
        return True
    return False

while True:
    INSIDE = 0
    OUTSIDE = 1
    CNT = 2
    NUM = {}

    arr = []
    for i in range(MIN_I,MAX_I+1):
        for j in range(MAX_J+1):
            if is_valid(i,j):
                NUM[(i,j)] = CNT
                CNT += 1
                arr.append((i,j))

    uf = UnionFind(CNT)

    random.shuffle(arr)
    taken = set()
    for (i,j) in arr:
        # if sees_inside(i,j):
        #     taken.add(NUM[(i,j)])
        adj = []
        for di in range(-1,2):
            for dj in range(-1,2):
                if abs(di)+abs(dj) == 1:
                    nxt = (i+di, j+dj)
                    if nxt in NUM and NUM[nxt] in taken:
                        adj.append(NUM[nxt])
        if sees_outside(i,j):
            adj.append(OUTSIDE)
        if sees_inside(i,j):
            adj.append(INSIDE)
        ok = True
        comps = set()
        for x in adj:
            comp = uf.find(x)
            if comp in comps:
                ok = False
            comps.add(comp)

        if uf.find(INSIDE) in comps and uf.find(OUTSIDE) in comps:
            if not possible:
                ok = False

        if ok:
            for x in adj:
                uf.union(x,NUM[(i,j)])
            taken.add(NUM[(i,j)])

    res = []
    for (i,j) in arr:
        if NUM[(i,j)] not in taken:
            x,y = get_point(i,j)
            res.append((x,y))

    if len(res) > MAX_N:
        continue

    print(len(res))
    for (x,y) in res:
        print(x,y)

    break

