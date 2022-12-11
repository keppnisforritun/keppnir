import sys

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

class Wall(object):
    def __init__(self, pos, h):
        self.pos = pos
        self.h = h

    def __str__(self):
        return ('pos' if self.pos else 'neg') + ' wall, height ' + str(self.h)

class Circle(object):
    def __init__(self, x, y, r):
        self.x = x
        self.y = y
        self.r = r

    def __str__(self):
        return 'circle %d,%d radius %d' % (self.x,self.y,self.r)

def dist_squared(a,b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2

def can_pass_between(a,b):
    if type(b) is Wall:
        a,b = b,a
    if type(a) is Wall:
        if type(b) is Wall:
            return True

        if a.pos != (b.x > 0):
            return True

        return b.y - a.h >= b.r
    else:
        return dist_squared((a.x,a.y),(b.x,b.y)) >= (a.r + b.r)**2

things = [
        Wall(True, 25),
        Wall(False, 25)
]

n = int(sys.stdin.readline().strip())

for i in range(n):
    x,y = map(int,sys.stdin.readline().strip().split())
    things.append(Circle(x, y, 40 + 25))

uf = UnionFind(len(things))
for i in range(len(things)):
    for j in range(len(things)):
        if i == j:
            continue
        if not can_pass_between(things[i], things[j]):
            # print(things[i], things[j])
            # print(i,j)
            uf.union(i,j)

if uf.find(0) == uf.find(1):
    print('impossible')
else:
    print('possible')

