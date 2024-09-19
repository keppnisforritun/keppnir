#!/usr/bin/python3
import sys, random, math

random.seed(int(sys.argv[-1]))

typ = sys.argv[1]
max_n = eval(sys.argv[2])

def contains(ptx, pty, ox, oy, r, h):
    if h >= r:
        return False
    dx = ptx - ox
    dy = pty - oy
    return dx * dx + dy * dy < r * r - h * h
    

n = random.choice([max_n, random.randint(4 * max_n // 5, max_n)])
max_m = min(10 ** 5, 4 * n)
m = random.choice([max_m, random.randint(4 * max_m // 5, max_m)])
h = random.randint(0, 4)

print(n, h)

if typ == "circle":
    pts = []
    x = random.randint(9 * 10 ** 8, 10 ** 9)
    y = random.randint(9 * 10 ** 8, 10 ** 9)
    if random.randint(1, 2) == 1:
        x = -x
    if random.randint(1, 2) == 1:
        y = -y
    pts.append((x, y))
    x = random.randint(-1000, 1000)
    y = random.randint(-1000, 1000)
    pts.append((x, y))

    rad_fac = eval(sys.argv[3])

    print(*pts[0])
    print(*pts[1])

    loc = []
    done = set()

    while len(loc) < n:
        th = random.uniform(0, 2 * math.pi)
        x = math.cos(th) * 1e8
        y = math.sin(th) * 1e8
        x = round(x)
        y = round(y)
        if (x, y) in done:
            continue
        done.add((x, y))
        loc.append((x, y))
        print(x, y)

    rs = [0 for _ in range(n)]

    print(m)

    left = m
    while left > 0:
        i = random.randint(0, n - 1)
        rad = round(random.uniform(1, 1e8 / n * rad_fac))
        if rs[i] > rad:
            continue
        if contains(*pts[0], *loc[i], rad, h):
            continue
        if contains(*pts[1], *loc[i], rad, h):
            continue
        print(i + 1, rad)
        rs[i] = rad
        left -= 1

if typ == "infty":
    pts = []
    pts.append((10**8//2,10**8//2))
    pts.append((-10**8//2,-10**8//2))

    rad_fac = eval(sys.argv[3])

    print(*pts[0])
    print(*pts[1])
    
    loc = []
    done = set()

    while len(loc) < n:
        th = random.uniform(0, 2 * math.pi)
        x = math.cos(th) * 1e7
        y = math.sin(th) * 1e7
        x = round(x)
        y = round(y)
        j = random.randint(0, 1)
        x += pts[j][0]
        y += pts[j][1]
        if (x, y) in done:
            continue
        done.add((x, y))
        loc.append((x, y))
        print(x, y)

    rs = [0 for _ in range(n)]

    print(m)

    left = m
    while left > 0:
        i = random.randint(0, n - 1)
        rad = round(random.uniform(1, 1e7 / n * rad_fac))
        if rs[i] > rad:
            continue
        if contains(*pts[0], *loc[i], rad, h):
            continue
        if contains(*pts[1], *loc[i], rad, h):
            continue
        print(i + 1, rad)
        rs[i] = rad
        left -= 1

if typ == "cluster":
    pts = []
    pts.append((-10**8,0))
    pts.append((10**8,0))

    print(*pts[0])
    print(*pts[1])
    
    marked_loc = []

    for j in range(2):
        for i in range(20):
            th = 2 * math.pi * i / 20
            x = math.cos(th) * 1e5
            y = math.sin(th) * 1e5
            x = round(x)
            y = round(y)
            x += pts[j][0]
            y += pts[j][1]
            marked_loc.append((x, y, 1))

    done = set()
    while len(done) < n - 40:
        x = random.randint(-10**4, 10**4)
        y = random.randint(-10**4, 10**4)
        if (x, y) in done:
            continue
        marked_loc.append((x, y, 0))
        done.add((x, y))

    random.shuffle(marked_loc)

    circles, clusters = [], []

    for i in range(n):
        print(marked_loc[i][0], marked_loc[i][1])
        if marked_loc[i][2]:
            circles.append(i)
        else:
            clusters.append(i)

    rs = [0 for _ in range(n)]

    print(m)

    updates = []

    for i in circles:
        updates.append((i, 10**5//2))

    while len(updates) < m:
        i = random.choice(clusters)
        rad = random.randint(1, 10**6)
        if rs[i] > rad:
            continue
        if contains(*pts[0], marked_loc[i][0], marked_loc[i][1], rad, h):
            continue
        if contains(*pts[1], marked_loc[i][0], marked_loc[i][1], rad, h):
            continue
        updates.append((i, rad))

    random.shuffle(updates)

    for i, r in updates:
        print(i + 1, r)

if typ == "dilkar":
    k = 5
    offs = float(sys.argv[3])
    st = (-50*n,0)
    nd = (50*n,50*n)
    print(*st)
    print(*nd)
    xs, ys = [], []
    for i in range(n//2):
        ang = (i % k) * 2 * math.pi / k
        ang += i * offs
        r = (i // k + 1) * 1000
        x = round(r * math.cos(ang))
        y = round(r * math.sin(ang))
        xs.append(x)
        ys.append(y)
        assert abs(x) <= 10 ** 9
        assert abs(y) <= 10 ** 9
        print(x, y)
    for i in range((n+1)//2):
        ang = 2 * math.pi / ((n+1)//2) * i
        r = ((n//2) //k + 2) * 1000
        x = round(r * math.cos(ang))
        y = round(r * math.sin(ang))
        xs.append(x)
        ys.append(y)
        print(x, y)
        assert abs(x) <= 10 ** 9
        assert abs(y) <= 10 ** 9
    assert len(xs) == n
    assert len(set((xs[i], ys[i]) for i in range(n))) == n
    print(n)
    for i in range(n):
        r = random.randint(1000, 3000)
        dx1 = xs[i] - st[0]
        dy1 = ys[i] - st[1]
        dx2 = xs[i] - nd[0]
        dy2 = ys[i] - nd[1]
        nrm1 = dx1 * dx1 + dy1 * dy1
        nrm2 = dx2 * dx2 + dy2 * dy2
        assert nrm1 > r * r
        assert nrm2 > r * r
        print(i + 1, random.randint(1000, 3000))

