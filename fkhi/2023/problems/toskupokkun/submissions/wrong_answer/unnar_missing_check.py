import sys
n, t = map(int, input().split())

L = []
lo, hi = 0, 0
for i in range(n):
    L.append(sorted(list(map(int, input().split()))))
    hi = max(hi, L[i][2])

ans = -1
while lo <= hi:
    m = (lo + hi) // 2
    time = 0
    for i in range(n):
        if L[i][2] <= m:
            time += L[i][0]
        else: 
            time += L[i][2]
        if time > t:
            break
    if time <= t:
        ans = m
        hi = m-1
    else:
        lo = m+1
            
if ans == -1:
    print("Omogulegt!")
else:
    print(ans)
