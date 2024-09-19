#!/usr/bin/python3
import sys, collections, math, string
from random import seed, randint, choice, shuffle

def gen_tree(n, deg_gen, order = "in"):
    if n == 0:
        return [], []
    queue = collections.deque()
    left = list(range(1, n))
    par = [0 for i in range(n)]
    ch = [[] for i in range(n)]
    queue.append(0)
    while len(queue) > 0 and len(left) > 0:
        cur = queue.popleft()
        d = deg_gen()
        for i in range(d):
            if len(left) == 0:
                break
            j = randint(0, len(left) - 1)
            left[-1], left[j] = left[j], left[-1]
            ch[cur].append(left[-1])
            par[left[-1]] = cur
            left.pop()
        for x in ch[cur]:
            if order == "pre":
                queue.appendleft(x)
            else:
                queue.append(x)
    return (par, ch)

class StringMaker:
    def __init__(self):
        self.l = 1
        self.c = ['a']
    def get_next(self):
        ret = ''.join(self.c)
        for i in range(len(self.c)):
            if self.c[i] == 'z':
                self.c[i] = 'a'
            else:
                self.c[i] = chr(ord(self.c[i]) + 1)
                return ret
        self.l += 1
        self.c = ['a' for i in range(self.l)]
        return ret
    def get(self):
        ret = "jord"
        while ret == "jord":
            ret = self.get_next()
        return ret

maker = StringMaker()

seed(int(sys.argv[-1]))

max_n = eval(sys.argv[1])
max_x = eval(sys.argv[2])
case = sys.argv[3]

n = choice([max_n, randint(max_n // 2, max_n)])
n = max(1, n)
chars = list(string.ascii_lowercase)
oth_names = [maker.get() for _ in range(4 * n)]
shuffle(oth_names)
names = ["jord"] + oth_names[:n - 1]

xs = [randint(1, max_x) for i in range(n)]
par, ch = [], []

if case == "random":
    case = choice(["tower", "bst", "slantbst", "mixbst", "flat", "sqrt", "log"])

if case == "tower":
    par, ch = gen_tree(n, lambda : 1)
    
if case == "bst":
    par, ch = gen_tree(n, lambda : 2)

if case == "slantbst":
    par, ch = gen_tree(n, lambda : 2, "pre")

if case == "mixbst":
    par, ch = gen_tree(n, lambda : randint(1, 2))

if case == "flat":
    par, ch = gen_tree(n, lambda : randint(1, n))

if case == "sqrt":
    m = int(round(math.sqrt(n)))
    par, ch = gen_tree(n, lambda : randint(1, m))

if case == "log":
    m = int(round(math.log(n)))
    par, ch = gen_tree(n, lambda : randint(1, m))

for i in range(n):
    if len(ch[i]) > 0:
        xs[i] = -1

print(n)
for i in range(n):
    print(names[i], names[par[i]], xs[i])
