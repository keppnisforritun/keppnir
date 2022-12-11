import sys
n = int(sys.stdin.readline())
arr = []
for i in range(n):
    d, c = map(int, sys.stdin.readline().strip().split())
    arr.append((d,c))

arr = sorted(arr)[::-1]
need = arr[0][1]
last = arr[0][0]
for i in range(1,len(arr)):
    d, c = arr[i]
    between = last - d - 1
    assert between >= 0
    need -= between
    need = max(need, 0)
    need += c
    last = d

need = need - last

if need > 0:
    print('      IMPOSSIBLE          ')
else:
    print(-need)

