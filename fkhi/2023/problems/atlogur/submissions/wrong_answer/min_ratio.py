n = int(input())
knights = [list(map(int, input().split())) for _ in range(n)]
print(min(range(1, n+1), key=lambda i: knights[i-1][1]/knights[i-1][0]))
