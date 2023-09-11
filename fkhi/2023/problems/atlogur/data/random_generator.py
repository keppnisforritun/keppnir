import random
import sys

random.seed(sys.argv[-1])
min_n = int(sys.argv[1])
max_n = int(sys.argv[2])
min_h = int(sys.argv[3])
max_h = int(sys.argv[4])
min_s = int(sys.argv[5])
max_s = int(sys.argv[6])
sort_mode = sys.argv[7].lower()

assert sort_mode in ["none"] or all(c in "hsad" for c in sort_mode)

n = random.randint(min_n, max_n)

healths = [random.randint(min_h, max_h) for _ in range(n)]
damages = [random.randint(min_s, max_s) for _ in range(n)]

if "h" in sort_mode:
    healths = sorted(healths)
if "hd" in sort_mode:
    healths = reversed(healths)

if "s" in sort_mode:
    damages = sorted(damages)
if "sd" in sort_mode:
    damages = reversed(damages)
knights = zip(healths, damages)

print(n)
for health, damage in knights:
    print(f"{health} {damage}")
