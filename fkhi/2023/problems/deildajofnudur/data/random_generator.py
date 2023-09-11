import random
import sys

from string import ascii_lowercase

random.seed(sys.argv[-1])
min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
min_k = int(sys.argv[3])
max_k = int(sys.argv[4])

n = random.randint(min_n, max_n)
k = random.randint(min_k, max_k)

arr = [random.choice(ascii_lowercase) for _ in range(n)]

if k == 1:
    x = random.choice(ascii_lowercase)
    arr = [x for _ in range(n)]
if k == 2:
    chars = list(ascii_lowercase)
    random.shuffle(chars)
    for i in range(0, n, 2):
        arr[i] = chars[0]
    last = arr[0]
    for i in range(1, n, 2):
        cur = last
        while cur == last:
            cur = random.choice(chars[1:])
        arr[i] = cur
        last = cur
elif k > 2:
    k = min(k, n)
    divisors = []
    for i in range(1, 27):
        if k % i == 0:
            divisors.append(i)
    div = random.choice(divisors)

    chars = list(ascii_lowercase)
    random.shuffle(chars)
    chars = chars[:div]

    repetitions = k // div

    replacement = chars * repetitions
    random.shuffle(replacement)

    i = random.randint(0, n - k)
    arr[i:i+k] = replacement

print(n)
print(''.join(arr))
