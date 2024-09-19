#!/usr/bin/python3
from itertools import combinations

n = int(input())
seq = list(map(int, input().split()))

all_edges = [(i, j) for i in range(n) for j in range(i+1, n)]

for k in range(len(all_edges) + 1):
    for comb in combinations(all_edges, k):
        temp = [0 for _ in range(n)]
        edges = []
        for (u, v) in comb:
            temp[u] += 1
            temp[v] += 1
            edges.append((u,v))
        if temp == seq:
            m = sum(seq) // 2
            print(f"{n} {m}")
            for (u, v) in edges:
                print(f"{u+1} {v+1}")
            exit()
print("Omogulegt!")
