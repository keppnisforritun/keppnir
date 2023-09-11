M = 1000000007

t = int(input())
for i in range(t):
    n = int(input())

    mem = [0 for i in range(n)]
    mem[0] = 1
    for i in range(1, n+1):
        nxt = list(mem)
        for j in range(n):
            nxt[j] = (nxt[j] + mem[(j+n-i)%n]) % M
        mem = nxt

    numer = mem[0]
    denom = pow(2, (M-2)*n, M)
    print(numer * denom % M)
