import random, sys, math

small_ang = 1e-6

def make_range(mn, mx, n):
    res = []
    for i in range(n):
        l = mn + i * (mx - mn) / (n + 1)
        r = mn + (i + 1) * (mx - mn) / (n + 1)
        res.append(random.uniform(l + (r - l) / 3, l + 2 * (r - l) / 3))
    return res

def my_sin(theta):
    if theta < small_ang:
        return theta
    return math.sin(theta)

def my_cos(theta):
    if theta < small_ang:
        return 1 - theta * theta / 2
    return math.cos(theta)

random.seed(sys.argv[-1])
min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
max_d = int(sys.argv[3])
data_type = sys.argv[4]

n = random.randint(min_n, max_n)

if data_type == "box":
    n -= n % 4
    mnx = random.randint(-max_d, max_d)
    mny = random.randint(-max_d, max_d)
    mxx = random.randint(-max_d, max_d)
    mxy = random.randint(-max_d, max_d)
    if mnx > mxx:
        mnx, mxx = mxx, mnx
    if mny > mxy:
        mny, mxy = mxy, mny
    print(n)
    print("{:d} {:d}".format(mnx, mny))
    for x in make_range(mnx, mxx, n // 4 - 1):
        print("{:d} {:d}".format(round(x), mny))
    print("{:d} {:d}".format(mxx, mny))
    for y in make_range(mny, mxy, n // 4 - 1):
        print("{:d} {:d}".format(mxx, round(y)))
    print("{:d} {:d}".format(mxx, mxy))
    for x in make_range(mnx, mxx, n // 4 - 1)[::-1]:
        print("{:d} {:d}".format(round(x), mxy))
    print("{:d} {:d}".format(mnx, mxy))
    for y in make_range(mny, mxy, n // 4 - 1)[::-1]:
        print("{:d} {:d}".format(mnx, round(y)))
elif data_type == "circle":
    cx = random.randint(-max_d // 4, max_d // 4)
    cy = random.randint(-max_d // 4, max_d // 4)
    r = random.randint(max_d // 2, 3 * max_d // 4)
    print(n)
    th_offs = random.uniform(0, 2 * math.pi)
    for theta in make_range(0, 2 * math.pi, n):
        x = round(cx + r * my_cos(th_offs + theta))
        y = round(cy + r * my_sin(th_offs + theta))
        print("{:d} {:d}".format(x, y))
elif data_type == "close_line":
    print(5)
    print("{:d} {:d}".format(-10, 10))
    print("{:d} {:d}".format(-50, -1))
    print("{:d} {:d}".format(50, -1))
    print("{:d} {:d}".format(10, 10))
    print("{:d} {:d}".format(0, 0))
elif data_type == "batman":
    print(17)
    print("{:d} {:d}".format(140,7666))
    print("{:d} {:d}".format(-5688,7749))
    print("{:d} {:d}".format(-2794,6385))
    print("{:d} {:d}".format(-3538,4360))
    print("{:d} {:d}".format(223,4112))
    print("{:d} {:d}".format(1917,2499))
    print("{:d} {:d}".format(3033,4112))
    print("{:d} {:d}".format(6010,4070))
    print("{:d} {:d}".format(5927,6261))
    print("{:d} {:d}".format(9730,8038))
    print("{:d} {:d}".format(4025,7790))
    print("{:d} {:d}".format(3777,6674))
    print("{:d} {:d}".format(2455,6096))
    print("{:d} {:d}".format(2372,7749))
    print("{:d} {:d}".format(1256,6922))
    print("{:d} {:d}".format(843,6302))
    print("{:d} {:d}".format(140,6757))
elif data_type == "comb":
    n -= n % 4
    print(n)
    base1 = random.randint(-max_d, 0)
    base2 = base1 + 1
    mnx = random.randint(-max_d, 0)
    mxx = random.randint(0, max_d)
    last_top = 0.0
    for i, x in list(enumerate(make_range(mnx, mxx, n // 2)))[::-1]:
        x = round(x)
        top = random.randint(max_d / 2, max_d)
        if i == n // 2 - 1:
            print("{:d} {:d}".format(mxx, base1))
            print("{:d} {:d}".format(mxx, top))
            last_top = top
        elif i == 0:
            print("{:d} {:d}".format(mnx, last_top))
            print("{:d} {:d}".format(mnx, base1))
        elif i % 2 == 0:
            print("{:d} {:d}".format(x, last_top))
            print("{:d} {:d}".format(x, base2))
        else:
            print("{:d} {:d}".format(x, base2))
            print("{:d} {:d}".format(x, top))
            last_top = top
elif data_type == "star":
    n -= n % 2
    r1 = random.randint(0.0, max_d / 4)
    r2 = random.randint(max_d / 4, max_d / 2)
    cx = random.randint(-max_d / 2, max_d / 2)
    cy = random.randint(-max_d / 2, max_d / 2)
    print(n)
    th_offs = random.uniform(0, 2 * math.pi)
    for i, theta in enumerate(make_range(0, 2 * math.pi, n)):
        r = r1 if i % 2 == 0 else r2
        x = round(cx + r * my_cos(th_offs + theta))
        y = round(cy + r * my_sin(th_offs + theta))
        print("{:d} {:d}".format(x, y))
elif data_type == "spiral":
    n -= n % 2
    print(n)
    sx = random.randint(-max_d // 3, max_d // 3)
    sy = random.randint(-max_d // 3, max_d // 3)
    theta_off = random.uniform(0, 2 * math.pi)
    rho = make_range(max_d // 3, 2 * max_d // 3, n // 2)
    revol = random.randint(1, max(1, n // 1000))
    delta_coeff = max_d / revol
    delta_rho = random.uniform(delta_coeff / 20.0, delta_coeff / 10.0)
    theta = make_range(0, 2 * revol * math.pi, n // 2)
    for i in range(n // 2 - 1):
        x = round(sx + rho[i] * my_cos(theta_off + theta[i]))
        y = round(sy + rho[i] * my_sin(theta_off + theta[i]))
        print("{:d} {:d}".format(x, y))
    x = round(sx + (rho[-1] - delta_rho / 2) * my_cos(theta_off + 11 * theta[-1] - 10 * theta[-2]))
    y = round(sy + (rho[-1] - delta_rho / 2) * my_sin(theta_off + 11 * theta[-1] - 10 * theta[-2]))
    print("{:d} {:d}".format(x, y))
    for i in reversed(range(n // 2 - 1)):
        x = round(sx + (rho[i] - delta_rho) * my_cos(theta_off + theta[i]))
        y = round(sy + (rho[i] - delta_rho) * my_sin(theta_off + theta[i]))
        print("{:d} {:d}".format(x, y))
    x = round(sx + (rho[0] - delta_rho / 2) * my_cos(theta_off + 11 * theta[0] - 10 * theta[1]))
    y = round(sy + (rho[0] - delta_rho / 2) * my_sin(theta_off + 11 * theta[0] - 10 * theta[1]))
    print("{:d} {:d}".format(x, y))
elif data_type == "randomsimple":
    # Uses https://github.com/spoiledhua/random-simple-polygon-generation
    with open(str(n) + ".txt", "r") as f:
        data = f.readlines()
        sx = random.randint(-max_d, 0)
        sy = random.randint(-max_d, 0)
        dl = random.randint(1, max_d)
        print(data[0].strip())
        for line in data[1:][::-1]:
            x, y = map(float, line.strip().split())
            print("{:d} {:d}".format(int(dl * x + sx), int(dl * y + sy)))
