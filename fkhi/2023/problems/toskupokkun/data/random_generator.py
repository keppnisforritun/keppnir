import random
import sys

def solve(n, t, dimensions):
    l, r = 0, 10 ** 9 + 10
    while r > l:
        m = l + (r - l) // 2
        curt, valid = 0, True
        for i in range(n):
            if dimensions[i][1] > m:
                valid = False
                break
            if dimensions[i][2] <= m:
                curt += dimensions[i][0]
            else:
                curt += dimensions[i][2]
        if (not valid) or curt > t:
            l = m + 1
        else:
            r = m
    return l

random.seed(sys.argv[-1])

max_n = int(sys.argv[1])
max_x = int(sys.argv[2])
max_y = int(sys.argv[3])
max_z = int(sys.argv[4])

if max_x < 0:
    dimensions = []
    curt = 0
    for i in range(max_n):
        x = random.randint(1, 10 ** 9)
        curt += x
        y = random.randint(x, 10 ** 9)
        z = random.randint(10 ** 9 - 100, 10 ** 9)
        dim = [x, y, z]
        random.shuffle(dim)
        dimensions.append(dim)
    print(max_n, curt)
    for x, y, z in dimensions:
        print(x, y, z)
    exit(0)

n = random.randint(max(1, max_n - 100), max_n)
dimensions = [[random.randint(1, max_x), random.randint(1, max_y), random.randint(1, max_z)] for i in range(n)]
for i in range(n):
    dimensions[i].sort()
impossible_left, impossible_right = 0, 10 ** 18 + 10
while impossible_right > impossible_left:
    impossible_mid = impossible_right - (impossible_right - impossible_left) // 2
    if solve(n, impossible_mid, dimensions) == 10 ** 9 + 10:
        impossible_left = impossible_mid
    else:
        impossible_right = impossible_mid - 1
mn = max([l[1] for l in dimensions])
unchanging_left, unchanging_right = impossible_left, 10 ** 18 + 10
while unchanging_right > unchanging_left:
    unchanging_mid = unchanging_left + (unchanging_right - unchanging_left) // 2
    if solve(n, unchanging_mid, dimensions) == mn:
        unchanging_right = unchanging_mid
    else:
        unchanging_left = unchanging_mid + 1
t = 0
case = random.randint(1, 8)
if case == 1:
    t = max(0, impossible_left - random.randint(1, 5))
elif case == 2:
    t = random.randint(0, sum(max(d) for d in dimensions))
else:
    t = random.randint(impossible_left, unchanging_left)
print(n, t)
for i in range(n):
    random.shuffle(dimensions[i])
    print(*dimensions[i])

