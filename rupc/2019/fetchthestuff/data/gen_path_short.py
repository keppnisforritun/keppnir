import sys
import random

random.seed(int(sys.argv[-1]))
n = int(sys.argv[1])
m = int(sys.argv[2])
k = int(sys.argv[3])

start = 1
end = n

arr = [ i for i in range(2,n) ]
random.shuffle(arr)
items = arr[:k]
assert len(items) == k
random.shuffle(arr)

arr = [start] + arr + [end]
es = []
for (a,b) in zip(arr,arr[1:]):
    es.append((a,b,'locked'))

for l in range(2,n+1):
    if len(es) >= m:
        break
    for i in range(n):
        if len(es) >= m:
            break
        if i+l >= n:
            break
        es.append((arr[i], arr[i+l], 'locked'))

print('%d %d %d' % (n,len(es),k))
print(' '.join(map(str, items)))
random.shuffle(es)
for (a,b,c) in es:
    print('%d %d %s' % (a,b,c))

