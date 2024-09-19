#!/usr/bin/python3
import sys
import random

class UGUF:
    def __init__(self, n):
        self.fst = list(range(n))
        self.lst = list(range(n))
        self.nxt = [-1 for i in range(n)]
        self.ops = []

    def print_group(self, x):
        x = self.find(x)
        sys.stdout.write(f"{x + 1} ")
        while self.nxt[x] >= 0:
            x = self.nxt[x]
            sys.stdout.write(f"{x + 1} ")
        sys.stdout.write("\n")

    def undo(self):
        if len(self.ops) == 0:
            return
        if self.ops[-1] != ():
            self.nxt[self.ops[-1][0]] = self.ops[-1][1]
            self.ops.pop()
            self.nxt[self.ops[-1][0]] = self.ops[-1][1]
            self.ops.pop()
            self.fst[self.ops[-1][0]] = self.ops[-1][1]
            self.ops.pop()
            self.lst[self.ops[-1][0]] = self.ops[-1][1]
        self.ops.pop()

    def find(self, x):
        while self.fst[x] != x:
            x = self.fst[x]
        return x

    def size(self, x):
        x = self.find(x)
        return -self.nxt[self.lst[x]]

    def unite(self, x, y):
        x, y = self.find(x), self.find(y)
        if x == y:
            self.ops.append(())
            return
        if self.nxt[self.lst[x]] > self.nxt[self.lst[y]]:
            x, y = y, x
        self.ops.append((x, self.lst[x]))
        self.ops.append((y, self.fst[y]))
        self.ops.append((self.lst[x], self.nxt[self.lst[x]]))
        self.ops.append((self.lst[y], self.nxt[self.lst[y]]))
        self.nxt[self.lst[y]] += self.nxt[self.lst[x]] 
        self.nxt[self.lst[x]] = self.fst[y]
        self.fst[y] = x
        self.lst[x] = self.lst[y]

random.seed(int(sys.argv[-1]))

max_n = int(sys.argv[1])
max_q = int(sys.argv[2])

n = random.choice([max_n, random.randint(max_n // 2, max_n)])
q = random.choice([max_q, random.randint(max_q // 2, max_q)])

print_quota = 10 ** 6
print(n, q)
uf = UGUF(n)

while q > 0:
    if random.randint(1, 4) == 1:
        x = random.randint(0, n - 1)
        if uf.size(x) <= print_quota:
            print('p', x + 1)
            print_quota -= uf.size(x)
            q -= 1
        continue
    if random.randint(1, 3) == 1:
        if len(uf.ops) > 0:
            print('u')
            uf.undo()
            q -= 1
        continue
    x = random.randint(0, n - 1)
    y = random.randint(0, n - 1)
    if uf.find(x) == uf.find(y):
        if random.randint(1, 100) != 1:
            continue
    print('j', x + 1, y + 1)
    uf.unite(x, y)
    q -= 1
