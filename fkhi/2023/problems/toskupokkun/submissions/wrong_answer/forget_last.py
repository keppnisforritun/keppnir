import sys
n, t = map(int, input().split())
bags = sorted([sorted(map(int, sys.stdin.readline().split())) for _ in range(n)], key=lambda b: b[2])

sm = sum(z for x,y,z in bags)
last = max(bags, key=lambda b: b[1])[1]
i = 0
for i in range(n):
    if bags[i][2] <= last:
        sm += bags[i][0] - bags[i][2]
    else:
        if sm <= t:
            print(last)
            exit()

        last = bags[i][2]
        sm += bags[i][0] - bags[i][2]

print("Omogulegt!")
