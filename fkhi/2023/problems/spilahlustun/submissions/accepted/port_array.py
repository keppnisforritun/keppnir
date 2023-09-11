import sys
sys.setrecursionlimit(600000)

class SplayTree:
    def __init__(self):
        self.left = []
        self.right = []
        self.parent = []
        self.key = []
        self.reversed = []
        self.size = []
        self.root = -1

    def push(self, i):
        if self.reversed[i]:
            if self.left[i] != -1:
                self.reversed[self.left[i]] = not self.reversed[self.left[i]]
            if self.right[i] != -1:
                self.reversed[self.right[i]] = not self.reversed[self.right[i]]
            self.reversed[i] = False
            self.key[i] = -self.key[i]
            self.left[i], self.right[i] = self.right[i], self.left[i]

    def update_size(self, i):
        self.size[i] = 1
        if self.left[i] != -1:
            self.size[i] += self.size[self.left[i]]
        if self.right[i] != -1:
            self.size[i] += self.size[self.right[i]]

    def inorder(self, i):
        if i == -1:
            return
        self.push(i)
        self.inorder(self.left[i])
        print(self.key[i], end=" ")
        self.inorder(self.right[i])

    def left_rotate(self, x):
        y = self.right[x]
        if y != -1:
            self.right[x] = self.left[y]
            if self.left[y] != -1:
                self.parent[self.left[y]] = x
            self.parent[y] = self.parent[x]
        if self.parent[x] == -1:
            self.root = y
        elif x == self.left[self.parent[x]]:
            self.left[self.parent[x]] = y
        else:
            self.right[self.parent[x]] = y
        if y != -1:
            self.left[y] = x
        if self.parent[x] != -1:
            self.update_size(self.parent[x])
        self.update_size(x)
        if y != -1:
            self.update_size(y)
        self.parent[x] = y

    def right_rotate(self, x):
        y = self.left[x]
        if y != -1:
            self.left[x] = self.right[y]
            if self.right[y] != -1:
                self.parent[self.right[y]] = x
            self.parent[y] = self.parent[x]
        if self.parent[x] == -1:
            self.root = y
        elif self.left[self.parent[x]] == x:
            self.left[self.parent[x]] = y
        else:
            self.right[self.parent[x]] = y
        if y != -1:
            self.right[y] = x
        if self.parent[x] != -1:
            self.update_size(self.parent[x])
        self.update_size(x)
        if y != -1:
            self.update_size(y)
        self.parent[x] = y

    def splay(self, x, lim = -1):
        while self.parent[x] != lim:
            if self.parent[self.parent[x]] == lim:
                if self.left[self.parent[x]] == x:
                    self.right_rotate(self.parent[x])
                else:
                    self.left_rotate(self.parent[x])
            elif self.left[self.parent[x]] == x and self.left[self.parent[self.parent[x]]] == self.parent[x]:
                self.right_rotate(self.parent[self.parent[x]])
                self.right_rotate(self.parent[x])
            elif self.right[self.parent[x]] == x and self.right[self.parent[self.parent[x]]] == self.parent[x]:
                self.left_rotate(self.parent[self.parent[x]])
                self.left_rotate(self.parent[x])
            elif self.left[self.parent[x]] == x and self.right[self.parent[self.parent[x]]] == self.parent[x]:
                self.right_rotate(self.parent[x])
                self.left_rotate(self.parent[x])
            else:
                self.left_rotate(self.parent[x])
                self.right_rotate(self.parent[x])

    def insert(self, key):
        z, p = self.root, -1

        while z != -1:
            self.push(z)
            p = z
            z = self.right[z]

        self.left.append(-1)
        self.right.append(-1)
        self.parent.append(p)
        self.key.append(key)
        self.reversed.append(False)
        self.size.append(1)
        z = len(self.key) - 1

        if p == -1:
            self.root = z
        else:
            self.right[p] = z

        self.splay(z)

    def reverse(self, i, j):
        if i == 0 and j == self.size[self.root] - 1:
            self.reversed[self.root] = not self.reversed[self.root]
        elif i == 0:
            self.splay(self.kth_node(j + 1))
            self.push(self.root)
            if self.left[self.root] != -1:
                self.reversed[self.left[self.root]] = not self.reversed[self.left[self.root]]
        elif j == self.size[self.root] - 1:
            self.splay(self.kth_node(i - 1))
            self.push(self.root)
            if self.right[self.root] != -1:
                self.reversed[self.right[self.root]] = not self.reversed[self.right[self.root]]
        else:
            self.splay(self.kth_node(i - 1))
            self.push(self.root)
            self.splay(self.kth_node(j + 1), self.root)
            self.update_size(self.root)
            if self.left[self.right[self.root]] != -1:
                self.reversed[self.left[self.right[self.root]]] = not self.reversed[self.left[self.right[self.root]]]

    def kth_node(self, k):
        z = self.root
        while z != -1:
            self.push(z)
            lsz = 0 if self.left[z] == -1 else self.size[self.left[z]]
            if k == lsz:
                return z
            if k < lsz:
                z = self.left[z]
            else:
                z = self.right[z]
                k -= lsz + 1
        return z

if __name__ == '__main__':
    n, q = map(int, sys.stdin.readline().split())
    tree = SplayTree()
    for i in range(n):
        tree.insert(i + 1)
    for i in range(q):
        a, b = map(int, sys.stdin.readline().split())
        tree.reverse(a - 1, b - 1)
    tree.inorder(tree.root)
    print()
