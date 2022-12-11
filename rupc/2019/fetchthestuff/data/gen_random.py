import sys
import random

random.seed(int(sys.argv[-1]))

n = int(sys.argv[1])
m = int(sys.argv[2])
k = int(sys.argv[3])

# # n = random.randint(3,20)
# # n = random.randint(10, 100)
# # n = random.randint(10, 5000)
# n = random.randint(4000, 5000)
# # n = random.randint(10,15)
# # m = random.randint(1,n*(n-1))
# m = random.randint(1,min(n*(n-1), 10**5))
# k = random.randint(1,min(n-2, 30))
# k = random.randint(30,min(n-2, 30))

es = set()
while len(es) < m:
    a = random.randint(1,n)
    b = random.randint(1,n)
    if a != b:
        es.add((a,b, random.choice(['open', 'locked'])))

sys.stdout.write('%d %d %d\n' % (n, m, k))

used = set()
for i in range(k):
    while True:
        x = random.randint(2,n-1)
        if x not in used:
            break
    used.add(x)
    if i != 0:
        sys.stdout.write(' ')
    sys.stdout.write('%d' % x)
sys.stdout.write('\n')

es = list(es)
random.shuffle(es)
for (a,b,c) in es:
    sys.stdout.write('%d %d %s\n' % (a, b, c))

