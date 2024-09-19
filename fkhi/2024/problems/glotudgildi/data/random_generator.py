#!/usr/bin/python3
import sys, random

def landau(s):
    if len(s) == 0:
        return True
    n = len(s)
    s.sort()
    if s[0] < 0:
        return False
    if s[-1] >= n:
        return False
    sm = 0
    for i in range(n - 1):
        sm += s[i]
        if sm < i * (i + 1) // 2:
            return False
    sm += s[-1]
    return sm == n * (n - 1) // 2

random.seed(int(sys.argv[-1]))

typ = sys.argv[1]
n, score = 0, []

if typ == "manual":
    n = int(sys.argv[2])
    if n > 0:
        vals = sys.argv[3]
        assert len(vals) == n
        for c in vals:
            if ord('0') <= ord(c) and ord(c) <= ord('9'):
                score.append(ord(c) - ord('0'))
            else:
                score.append(ord(c) - ord('A') + 10)
    random.shuffle(score)

if typ == "max":
    n = int(sys.argv[2])
    for i in range(n // 2):
        score.append((n - 1) // 2)
    for i in range(n - n // 2):
        score.append(n // 2)
    random.shuffle(score)

if typ == "random" or typ == "fail":
    n = random.randint(12, 16)
    score = [0 for _ in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            if random.randint(1, 2) == 1:
                score[i] += 1
            else:
                score[j] += 1

if typ == "fail":
    while landau(score):
        i = random.randint(0, len(score) - 1)
        j = random.randint(0, len(score) - 1)
        if i == j:
            continue
        if score[i] + 1 >= n:
            continue
        if score[j] - 1 < 0:
            continue
        score[i] += 1
        score[j] -= 1

print(n)
print(*score)
