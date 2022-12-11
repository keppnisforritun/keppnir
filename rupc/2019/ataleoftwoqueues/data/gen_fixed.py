import sys
import random

random.seed(int(sys.argv[-1]))

p = int(sys.argv[1])
q = int(sys.argv[2])

def gen_with_sum(s):
    max_len_left = 5000
    res = []
    while s > 0:
        need = 1
        while need * max_len_left < s:
            need += 1
        here = random.randint(need, min(s, 60))
        res.append(here)
        max_len_left -= 1
        s -= here
    return res

L = gen_with_sum(p)
R = gen_with_sum(q)

assert len(L) <= 5000
assert len(R) <= 5000
assert sum(L) == p
assert sum(R) == q

targetL = random.randint(max(len(L),len(R)), 5000)
targetR = targetL

if random.randint(1,2) == 1:
    targetR = random.randint(max(len(L),len(R)), 5000)

while len(L) < targetL: L.append(0)
while len(R) < targetR: R.append(0)

random.shuffle(L)
random.shuffle(R)

sys.stdout.write('%d %d\n' % (len(L), len(R)))
print(' '.join(map(str, L)))
print(' '.join(map(str, R)))

