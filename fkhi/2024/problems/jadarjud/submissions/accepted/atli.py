#!/usr/bin/python3
import sys

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

if __name__ == "__main__":
    n, q = map(int, sys.stdin.readline().split())

    uf = UGUF(n)

    for _ in range(q):
        line = sys.stdin.readline()
        if line[0] == 'j':
            _, a, b = line.strip().split()
            a, b = int(a), int(b)
            a, b = a - 1, b - 1
            uf.unite(a, b)
        elif line[0] == 'u':
            uf.undo()
        elif line[0] == 'p':
            _, a = line.strip().split()
            a = int(a)
            a = a - 1
            uf.print_group(a)
