import sys
sys.setrecursionlimit(600000)

class SplayNode:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.parent = None
        self.key = key
        self.reversed = False
        self.size = 0
    def push(self):
        if self.reversed:
            if self.left is not None:
                self.left.reversed = not self.left.reversed
            if self.right is not None:
                self.right.reversed = not self.right.reversed
            self.reversed = False
            self.key = -self.key
            self.left, self.right = self.right, self.left
    def update_size(self):
        self.size = 1
        if self.left is not None:
            self.size += self.left.size
        if self.right is not None:
            self.size += self.right.size
    def inorder(self):
        self.push()
        l, r = self.left, self.right
        if l is not None:
            l.inorder()
        print(self.key, end=" ")
        if r is not None:
            r.inorder()

class SplayTree:
    def __init__(self):
        self.root = None

    def left_rotate(self, x):
        y = x.right
        if y is not None:
            x.right = y.left
            if y.left is not None:
                y.left.parent = x
            y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        if y is not None:
            y.left = x
        if x.parent is not None:
            x.parent.update_size()
        x.update_size()
        if y is not None:
            y.update_size()
        x.parent = y

    def right_rotate(self, x):
        y = x.left
        if y is not None:
            x.left = y.right
            if y.right is not None:
                y.right.parent = x
            y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        if y is not None:
            y.right = x
        if x.parent is not None:
            x.parent.update_size()
        x.update_size()
        if y is not None:
            y.update_size()
        x.parent = y

    def splay(self, x):
        while x.parent is not None:
            if x.parent.parent is None:
                if x.parent.left == x:
                    self.right_rotate(x.parent)
                else:
                    self.left_rotate(x.parent)
            elif x.parent.left == x and x.parent.parent.left == x.parent:
                self.right_rotate(x.parent.parent)
                self.right_rotate(x.parent)
            elif x.parent.right == x and x.parent.parent.right == x.parent:
                self.left_rotate(x.parent.parent)
                self.left_rotate(x.parent)
            elif x.parent.left == x and x.parent.parent.right == x.parent:
                self.right_rotate(x.parent)
                self.left_rotate(x.parent)
            else:
                self.left_rotate(x.parent)
                self.right_rotate(x.parent)

    def insert(self, key):
        z, p = self.root, None

        while z is not None:
            z.push()
            p = z
            z = z.right

        z = SplayNode(key)
        z.parent = p
        if p is None:
            self.root = z
        else:
            p.right = z

        self.splay(z)

    def split(self, k):
        other = SplayTree()
        z = self.kth_node(k)
        if z is None:
            return other
        self.splay(z)
        other.root = z.right
        z.right = None
        z.update_size()
        if other.root is not None:
            other.root.parent = None
        return other

    def join(self, other):
        if other.root is None:
            return
        if self.root is None:
            self.root = other.root
        else:
            n = self.kth_node(self.root.size - 1)
            self.splay(n)
            self.root.right = other.root
            self.root.right.parent = self.root
            self.root.update_size()

    def reverse(self, i, j):
        if i == 0:
            right = self.split(j)
            self.root.reversed = not self.root.reversed
            self.join(right)
        else:
            middle = self.split(i - 1)
            right = middle.split(j - i)
            middle.root.reversed = not middle.root.reversed
            middle.join(right)
            self.join(middle)

    def inorder(self):
        self.root.inorder()
        print("")

    def kth_node(self, k):
        z = self.root
        while z is not None:
            z.push()
            lsz = 0 if z.left is None else z.left.size
            if k == lsz:
                return z
            if k < lsz:
                z = z.left
            else:
                z = z.right
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
    tree.inorder()
