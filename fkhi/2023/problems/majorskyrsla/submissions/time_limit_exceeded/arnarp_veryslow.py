from itertools import permutations as pt
n, k = [int(x) for x in input().split()]

#taka venjulegan lista og flippa bara því sem ég þarf

def major_value(l):
    s = 0
    for x in range(len(l)):
        if x+1 != len(l) and l[x] > l[x+1]:
            s += x+1
        if s > k: return None
    if s == k:
        return ' '.join([str(x) for x in l])
    return None

n = [x+1 for x in range(n)]
val = None
for perm in pt(n):
    if val == None:
        val = major_value(perm)
print(val)
