#!/usr/bin/python3
import sys
inp = "\n".join(sys.stdin.readlines())
for i in range(len(inp)):
    for j in range(len(inp)):
        for k in range(len(inp)):
            if i > j:
                continue
            if i > k:
                continue
            if j > k:
                continue
            val = inp[i:j] + inp[j:k+1]
            x = None
            try:
                x = int(val)
            except ValueError:
                continue
            if val.strip() != val:
                continue
            if x != 69 and x != 420:
                continue
            print("Mergjad!")
            exit(0)
print("Leim!")
