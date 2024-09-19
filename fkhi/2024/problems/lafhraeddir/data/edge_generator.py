#!/usr/bin/python3
import sys, string, random

typ = sys.argv[1]
random.seed(int(sys.argv[-1]))

if typ == "leone":
    print(1, 1)
    print("apple", 10, 100)
    print("doctor", 8, 13, 0)

if typ == "maxdays":
    print(1, 500)
    for i in range(500):
        nam = string.ascii_lowercase[i % 25] + string.ascii_lowercase[i // 25]
        st = random.randint(10 ** 8, 10 ** 9)
        cn = 10 ** 9
        print(nam, st, cn)
    st = random.randint(10 ** 7, 10 ** 8)
    print("doctor", st, 1, 0)

if typ == "fullimmunity":
    print(20, 20)
    for i in range(20):
        nam = string.ascii_lowercase[i]
        st = random.randint(10 ** 8, 10 ** 9)
        cn = random.randint(1, 10 ** 9)
        print(nam, st, cn)
    sup = random.randint(0, 19)
    for i in range(20):
        nam = "a" + string.ascii_lowercase[i]
        st = random.randint(10 ** 7, 10 ** 8)
        cn = random.randint(1, 10 ** 2)
        imm = [string.ascii_lowercase[j] for j in range(20)]
        random.shuffle(imm)
        if i != sup:
            imm = imm[:random.randint(0, 5)]
        print(nam, st, cn, len(imm), *imm)

