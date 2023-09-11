import sys
import random

if __name__ == "__main__":
    n, t = map(int, sys.stdin.readline().strip().split())
    dims = [sorted(list(map(int, sys.stdin.readline().strip().split()))) for i in range(n)]
    random.shuffle(dims)
    l, r = 0, 10 ** 9 + 10
    while r > l:
        m = l + (r - l) // 2
        curt, valid = 0, True
        for i in range(n):
            if dims[i][1] > m:
                valid = False
                break
            if dims[i][2] <= m:
                curt += dims[i][0]
            else:
                curt += dims[i][2]
        if (not valid) or curt > t:
            l = m + 1
        else:
            r = m
    if l == 10 ** 9 + 10:
        sys.stdout.write("Omogulegt!\n")
    else:
        sys.stdout.write(str(l) + "\n")
