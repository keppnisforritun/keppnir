import sys

sys.stdin.readline()

res = []
at = 0
for line in sys.stdin:
    a, b = map(int, line.strip().split())
    # res.append('"c%03d = Circle((%d,%d),40)"' % (at, a,b))
    res.append('"c%03d = Circle((%d,%d),65)"' % (at, a,b))
    at += 1

print("Execute({%s})" % ','.join(res))

