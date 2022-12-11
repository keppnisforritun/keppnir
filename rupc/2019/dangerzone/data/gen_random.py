import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
min_dist = int(sys.argv[2])
box = int(sys.argv[3])

while True:
    # sys.stderr.write('trying\n')
    restart = False
    tries = 50*n
    arr = []
    for i in range(n):
        while True:
            # sys.stderr.write('%d %d\n' % (tries, i))
            tries -= 1
            if tries < 0:
                restart = True
                break
            ok = True
            x = random.randint(-box, box)
            y = random.randint(40, box)
            if x**2 + y**2 <= 280**2:
                continue
            for (xp,yp) in arr:
                if (x-xp)**2 + (y-yp)**2 < min_dist**2:
                    ok = False
                    break
            if ok:
                break
        if restart:
            break
        arr.append((x,y))
    if not restart:
        break

print(n)
for (x,y) in arr:
    print(x,y)

