#!/usr/bin/python3

def read_time():
    x, s = input().strip().split()
    x = int(x)
    if s[:3] == "min":
        x *= 60
    if s[:3] == "klu":
        x *= 60 * 60
    if s[:3] == "dag":
        x *= 60 * 60 * 8
    if s[:3] == "vik":
        x *= 60 * 60 * 8 * 5
    if s == "ar":
        x *= 60 * 60 * 8 * 5 * 52
    return x

t1, _, frq = input().strip().split()
t1 = 5 * int(t1)

if frq != "arlega":
    t1 *= 52
if frq == "daglega":
    t1 *= 5

t1 *= read_time()
t2 = read_time()

if t2 > t1:
    print("Borgar sig ekki!")
else:
    print(t1 - t2)
