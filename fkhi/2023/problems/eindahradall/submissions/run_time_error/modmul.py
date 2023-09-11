import sys, math, random, itertools

def rho(n):
    for s in [2, 3, 5, 7, 11, 13, 1031]:
        x, y, d = s, s, 1
        while d == 1:
            x = (x * x + 1) % n
            y = (y * y + 1) % n
            y = (y * y + 1) % n
            d = math.gcd(abs(x - y), n)
        if d == n:
            continue
        return d
    return -1

def miller_rabin(n, k):
    if n % 2 == 0:
        return n == 2
    if n <= 3:
        return n == 3
    s, d = 0, n - 1
    while d % 2 == 0:
        d >>= 1
        s += 1
    for i in range(k):
        a = random.randint(2, n - 1)
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        ok = False
        for j in range(s - 1):
            x *= x
            x %= n
            if x == 1:
                return False
            if x == n - 1:
                ok = True
                break
        if not ok:
            return False
    return True

def eratos(n):
    res = [i for i in range(n + 1)]
    for i in range(2, n + 1):
        if res[i] == i:
            for j in range(i * i, n + 1, i):
                res[j] = i
    return [x for x in range(2, n + 1) if res[x] == x]

def factor(n, prim):
    fac = dict()
    for p in prim:
        while n % p == 0:
            n //= p
            if p not in fac:
                fac[p] = 0
            fac[p] += 1
    st = []
    st.append(n)
    while len(st) > 0:
        y = st[-1]
        st.pop()
        if y == 1:
            continue
        if y in fac or miller_rabin(y, 5):
            if y not in fac:
                fac[y] = 0
            fac[y] += 1
        else:
            d = rho(y)
            st.append(d)
            st.append(y // d)
    return fac
 
if __name__ == "__main__":
    era = eratos(10 ** 4)
    for line in sys.stdin.readlines()[1:]:
        n = int(line)
        mod = 10 ** 9 + 7
        fac = factor(n, era)
        if 2 in fac:
            del fac[2]
        it = list(fac.items())
        ans = 0
        for e in itertools.product(*[range(x[1] + 1) for x in it]):
            d, phi = 1, 1
            for i in range(len(e)):
                if e[i] == 0:
                    continue
                d *= it[i][0] ** e[i]
                phi *= it[i][0] ** e[i] - it[i][0] ** (e[i] - 1)
            ans += (phi * pow(2, n // d, mod)) % mod
        ans *= pow(n, -1, mod)
        ans *= pow(2, -n, mod)
        ans %= mod
        print(ans)


