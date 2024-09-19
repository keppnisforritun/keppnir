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

n = int(sys.argv[1])
q = int(sys.argv[2])
typ = sys.argv[3]

if typ == "minn":
    print(1, 1)
    print("p", 1)

if typ == "testnop":
    print(2, 24)
    for _ in range(10):
        print("j", 1, 2)
    print("p", 2)
    for _ in range(5):
        print("u")
    print("p", 2)
    for _ in range(4):
        print("u")
    print("p", 2)
    print("u")
    print("p", 2)

if typ == "bst":
    queries = []
    left = list(range(n))
    nxt = []
    undoable = 0
    while len(left) > 1:
        while len(left) > 0:
            i = random.randint(0, len(left) - 1)
            left[i], left[-1] = left[-1], left[i]
            x = left[-1]
            left.pop()
            i = random.randint(0, len(left) - 1)
            left[i], left[-1] = left[-1], left[i]
            y = left[-1]
            left.pop()
            queries.append(f"j {x + 1} {y + 1}")
            undoable += 1
            nxt.append(x)
        z = random.choice(nxt)
        queries.append(f"p {z + 1}")
        left, nxt = nxt, left
    while undoable > 0:
        queries.append("u")
        undoable -= 1
    order = list(range(n))
    random.shuffle(order)
    for i in order[1:]:
        queries.append(f"p {i + 1}")
        x, y = i, order[0]
        if random.randint(1, 2) == 1:
            x, y = y, x
        if random.randint(1, 2) == 1:
            queries.append(f"j {x + 1} {y + 1}")
            undoable += 1
    queries.append(f"p {order[0] + 1}")
    assert len(queries) <= q
    print(n, len(queries))
    for l in queries:
        print(l)
