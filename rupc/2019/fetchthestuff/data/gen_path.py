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

while len(es) < m:
    a = random.randint(1,n)
    b = random.randint(1,n)
    if a < b:
        es.append((a,b,'locked'))

print('%d %d %d' % (n,len(es),k))
print(' '.join(map(str, items)))
random.shuffle(es)
for (a,b,c) in es:
    print('%d %d %s' % (a,b,c))

