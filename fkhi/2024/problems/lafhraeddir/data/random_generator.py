#!/usr/bin/python3
import sys, random, string

random.seed(int(sys.argv[-1]))

max_l = int(sys.argv[1])
max_e = int(sys.argv[2])
approx_d = eval(sys.argv[3])
str_rat = int(sys.argv[4])

taken = set()

def gen_name():
    while True:
        l = random.randint(1, 20)
        if l > 5:
            l = random.randint(1, 20)
        if l > 10:
            l = random.randint(1, 20)
        s = "".join([random.choice(string.ascii_lowercase) for _ in range(l)])
        if s in taken:
            continue
        taken.add(s)
        return s

L = random.choice([max_l, random.randint(max(1, max_l // 2), max_l)])
E = random.choice([max_e, random.randint(max(1, max_e // 2), max_e)])

print(L, E)

apples = []

for i in range(E):
    name = gen_name()
    apples.append(name)
    st = random.randint(1, 10 ** 9)
    cn = random.randint(1, 10 ** 9)
    print(name, st, cn)

mxcn = 2 * (10 ** 9 * E) // (L * approx_d)
mxcn = min(10 ** 9, mxcn)
mxcn = max(1, mxcn)

for i in range(L):
    name = gen_name()
    st = random.randint(1, 10 ** 9 // str_rat)
    cn = random.randint(1, mxcn)
    im_cnt = random.randint(0, 20)
    imm = random.sample(apples, im_cnt)
    print(name, st, cn, im_cnt, *imm)

