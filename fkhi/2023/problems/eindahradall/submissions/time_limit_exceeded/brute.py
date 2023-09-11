from itertools import combinations

M = 1000000007

t = int(input())
for i in range(t):
    n = int(input())
    L = list(range(1, n+1))
    numer = sum(1 for i in range(n+1) for comb in combinations(L, i) if sum(comb) % n == 0) % M
    denom = pow(2, (M-2)*n, M)
    print(numer * denom % M)
