#!/usr/bin/python3
import sys, random, itertools, string

def cur_len(opts):
    out = 0
    mx = [len(l) for l in opts]
    for inds in itertools.product(*[range(x) for x in mx]):
        for i in range(len(inds)):
            out += len(opts[i][inds[i]])
    return out

def make_str(mn, mx):
    l = random.randint(mn, mx)
    res = []
    for i in range(l):
        res.append(random.choice(string.ascii_letters))
    return "".join(res)

random.seed(int(sys.argv[-1]))

min_len = int(sys.argv[1])
max_len = int(sys.argv[2])
min_opt = int(sys.argv[3])
max_opt = int(sys.argv[4])

opts = []

while len(opts) < 100:
    nxt = random.randint(min_opt, max_opt)
    n_opt = [make_str(min_len, max_len) for _ in range(nxt)]
    if len(set(n_opt)) != len(n_opt):
        continue
    opts.append(n_opt)
    if cur_len(opts) > 10 ** 6:
        opts.pop()
        break

print(len(opts))
for l in opts:
    print(len(l), *l)
