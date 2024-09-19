#!/usr/bin/python3
import random, math, sys
from functools import cmp_to_key

def set_union(a, b, c):
    i, j = 0, 0
    while i < len(a) or j < len(b):
        if i == len(a):
            c.append(b[j])
            j += 1
        elif j == len(b):
            c.append(a[i])
            i += 1
        elif a[i] > b[j]:
            c.append(b[j])
            j += 1
        elif a[i] < b[j]:
            c.append(a[i])
            i += 1
        else:
            c.append(a[i])
            i += 1
            j += 1

class UnionFind:
    def __init__(self, n):
        self.p = [-1 for i in range(n)]
        self.c = n
    def find(self, x):
        if self.p[x] < 0:
            return x
        self.p[x] = self.find(self.p[x])
        return self.p[x]
    def united(self, x, y):
        return self.find(x) == self.find(y)
    def unite(self, x, y):
        a = self.find(x)
        b = self.find(y)
        if a == b:
            return
        if self.p[a] > self.p[b]:
            a, b = b, a
        self.p[a] += self.p[b]
        self.p[b] = a
        self.c -= 1
        return
    def size(self, x):
        return -self.p[self.find(x)]

class Pt3:
    def __init__(self, x = 0, y = 0, z = 0, i = -1):
        self.x = x
        self.y = y
        self.z = z
        self.i = i

    def is_zero(self):
        return self.x == 0 and self.y == 0 and self.z == 0

    def __add__(self, o):
        return Pt3(self.x + o.x, self.y + o.y, self.z + o.z)

    def __sub__(self, o):
        return Pt3(self.x - o.x, self.y - o.y, self.z - o.z)

    def cross(self, o):
        a = self.y * o.z - self.z * o.y
        b = self.z * o.x - self.x * o.z
        c = self.x * o.y - self.y * o.x
        return Pt3(a, b, c)

    def dot(self, o):
        a = self.x * o.x
        b = self.y * o.y
        c = self.z * o.z
        return a + b + c

    def sign(self, p2, p3):
        a = (self - p3).x * (p2 - p3).y
        b = (p2 - p3).x * (self - p3).y
        return a - b

    def in_triangle(self, p1, p2, p3):
        d1 = self.sign(p1, p2)
        d2 = self.sign(p2, p3)
        d3 = self.sign(p3, p1)
        has_neg = d1 < 0 or d2 < 0 or d3 < 0
        has_pos = d1 > 0 or d2 > 0 or d3 > 0
        return not (has_neg and has_pos)

class Face:
    def __init__(self, a, b, c, q):
        self.a = a
        self.b = b
        self.c = c
        self.q = q
        self.e1 = -1
        self.e2 = -1
        self.e3 = -1
        self.points = []
        self.dead = 10 ** 9

class HullMaker:
    def __init__(self):
        self.faces = []
        self.edges = []

    def glue(self, f1, f2):
        e1 = len(self.edges)
        self.edges.append(f2)
        e2 = len(self.edges)
        self.edges.append(f1)
        return (e1, e2)

    def prepare(self, p):
        random.seed(1337)
        n = len(p)
        random.shuffle(p)
        ve = [0]
        for i in range(1, n):
            if len(ve) == 1:
                if not (p[ve[0]] - p[i]).is_zero():
                    ve.append(i)
            elif len(ve) == 2:
                if not (p[ve[1]] - p[ve[0]]).cross(p[i] - p[ve[0]]).is_zero():
                    ve.append(i)
            elif (p[i] - p[ve[0]]).dot((p[ve[1]] - p[ve[0]]).cross(p[ve[2]] - p[ve[0]])) != 0:
                ve.append(i)
                break
        if len(ve) < 4:
            return False
        for i in range(len(ve)):
            p[i], p[ve[i]] = p[ve[i]], p[i]
        return True

    def sort2d(self, p):
        if len(p) < 1:
            return
        mn = 0
        for i in range(1, len(p)):
            if p[i].y < p[mn].y:
                mn = i
            if p[i].y > p[mn].y:
                continue
            if p[i].x < p[mn].x:
                mn = i
    
        p[0], p[mn] = p[mn], p[0]
        piv = p[0]
        p[1:] = sorted(p[1:], key=cmp_to_key(
            lambda a, b:
                (a.x - piv.x) * (b.y - piv.y) -
                    (b.x - piv.x) * (a.y - piv.y)
        ))

    def hull3(self, p):
        n = len(p)
        if not self.prepare(p):
            self.sort2d(p)
            return []

        f = []
        new_face = [-1 for _ in range(n)]
        conflict = [[] for _ in range(n)]

        def add_face(a, b, c):
            FF = len(self.faces)
            qq = (p[b] - p[a]).cross(p[c] - p[a])
            self.faces.append(Face(a, b, c, qq))
            f.append(FF)
            return FF

        F1 = add_face(0, 1, 2)
        F2 = add_face(0, 2, 1)
        self.faces[F1].e1, self.faces[F2].e3 = self.glue(F1, F2)
        self.faces[F1].e2, self.faces[F2].e2 = self.glue(F1, F2)
        self.faces[F1].e3, self.faces[F2].e1 = self.glue(F1, F2)

        for i in range(3, n):
            for F in [F1, F2]:
                Q = (p[i] - p[self.faces[F].a]).dot(self.faces[F].q)
                if Q > 0:
                    conflict[i].append(F)
                if Q >= 0:
                    self.faces[F].points.append(i)

        for i in range(3, n):
            for F in conflict[i]:
                self.faces[F].dead = min(self.faces[F].dead, i)
            v = -1
            for F in conflict[i]:
                if self.faces[F].dead != i:
                    continue

                parr = [self.faces[F].a, self.faces[F].b, self.faces[F].c]
                earr = [self.faces[F].e1, self.faces[F].e2, self.faces[F].e3]

                for j in range(3):
                    j2 = 0 if j == 2 else j + 1
                    if self.faces[self.edges[earr[j]]].dead > i:
                        Fn = add_face(parr[j], parr[j2], i)
                        new_face[parr[j]] = Fn

                        set_union(self.faces[F].points, self.faces[self.edges[earr[j]]].points, self.faces[Fn].points)

                        self.faces[Fn].points = [k for k in self.faces[Fn].points if (k > i and (p[k] - p[self.faces[Fn].a]).dot(self.faces[Fn].q) > 0)]
                        for k in self.faces[Fn].points:
                            conflict[k].append(Fn)

                        self.edges[earr[j] ^ 1] = Fn
                        self.faces[Fn].e1 = earr[j]
                        v = parr[j]
            
            if v == -1:
                continue

            while self.faces[new_face[v]].e2 == -1:
                u = self.faces[new_face[v]].b
                self.faces[new_face[v]].e2, self.faces[new_face[u]].e3 = self.glue(new_face[v], new_face[u])
                v = u

        f = [F for F in f if self.faces[F].dead >= n]
        return f

def touch(h, a, b, ra, rb):
    if h >= ra or h >= rb:
        return False
    ra2 = ra * ra - h * h
    rb2 = rb * rb - h * h
    dx = a.x - b.x
    dy = a.y - b.y
    nrm = dx * dx + dy * dy
    rhs = nrm - ra2 - rb2
    if rhs < 0:
        return True
    return 4 * ra2 * rb2 > rhs * rhs

def sgn(x):
    return (1 if x > 0 else 0) - (1 if x < 0 else 0)

class Point:
    def __init__(self, x = 0.0, y = 0.0):
        self.x = x
        self.y = y

    def __mul__(self, o):
        return self.x * o.y - self.y * o.x
    
    def __mod__(self, o):
        return self.x * o.x + self.y * o.y

    def __add__(self, o):
        return Point(self.x + o.x, self.y + o.y)
    
    def __sub__(self, o):
        return Point(self.x - o.x, self.y - o.y)

    def cross(self, a, b):
        return (a - self) * (b - self)

    def dist(self):
        return math.sqrt(self % self)

    def dist2(self):
        return self % self

    def scale(self, k):
        return Point(self.x * k, self.y * k)

def onSegment(s, e, p):
    return p.cross(s, e) == 0 and (s - p) % (e - p) <= 0

def segDist(s, e, p):
    if s == e:
        return (p - s).dist()
    d = (e - s).dist2()
    t = min(d, max(0.0, (p - s) % (e - s)))
    return (scale(p - s, d) - scale(e - s, t)).dist() / d

def inPolygon(p, a, strict = True):
    cnt = 0
    n = len(p)
    for i in range(n):
        q = p[(i + 1) % n]
        if onSegment(p[i], q, a):
            return not strict
        cnt ^= 1 if (((1 if a.y < p[i].y else 0) - (1 if a.y < q.y else 0)) * a.cross(p[i], q) > 0) else 0
    return cnt

n, h = map(int, sys.stdin.readline().strip().split())
stx, sty = map(int, sys.stdin.readline().strip().split())
ndx, ndy = map(int, sys.stdin.readline().strip().split())
xs, ys = [], []
for i in range(n):
    x, y = map(int, sys.stdin.readline().strip().split())
    xs.append(x)
    ys.append(y)
m = int(sys.stdin.readline())
js, rs = [], []
for i in range(m):
    j, r = map(int, sys.stdin.readline().strip().split())
    js.append(j - 1)
    rs.append(r)
lo, hi, brk = 0, m, -1
while hi > lo:
    md = hi - (hi - lo) // 2
    pts = []
    cur_r = [0 for _ in range(n)]
    ins = False
    for i in range(md):
        cur_r[js[i]] = max(cur_r[js[i]], rs[i])
    for i in range(n):
        z = xs[i] * xs[i] + ys[i] * ys[i] - cur_r[i] * cur_r[i] + h * h
        pts.append(Pt3(xs[i], ys[i], z, i))
        if cur_r[i] > h:
            dx1 = xs[i] - stx
            dy1 = ys[i] - sty
            dx2 = xs[i] - ndx
            dy2 = ys[i] - ndy
            n1 = dx1 * dx1 + dy1 * dy1
            n2 = dx2 * dx2 + dy2 * dy2
            rsq = (cur_r[i] - h) * (cur_r[i] - h)
            if n1 < rsq or n2 < rsq:
                ins = True
    if ins:
        hi = md - 1
        brk = md
        continue

    hm = HullMaker()
    res = hm.hull3(pts)
    if len(res) == 0:
        is_closed = True
        for i in range(len(pts)):
            j = (i + 1) % len(pts)
            if not touch(h, pts[i], pts[j], cur_r[pts[i].i], cur_r[pts[j].i]):
                is_closed = False
        if not is_closed:
            lo = md
        else:
            st = Point(stx, sty)
            nd = Point(ndx, ndy)
            poly = []
            for pt in pts:
                poly.append(Point(pt.x, pt.y))
            if inPolygon(poly, st) != inPolygon(poly, nd):
                hi = md - 1
                brk = md
            else:
                lo = md
        continue
    
    st_face = len(hm.faces)
    nd_face = len(hm.faces)

    face_uf = UnionFind(len(hm.faces) + 1)

    up = [False for _ in range(len(hm.faces))]

    for i in res:
        F = hm.faces[i]
        X = pts[F.b] - pts[F.a]
        Y = pts[F.c] - pts[F.a]
        Z = X.x * Y.y - X.y * Y.x
        up[i] = Z >= 0

    for i in res:
        F = hm.faces[i]
        if not touch(h, pts[F.a], pts[F.b], cur_r[pts[F.a].i], cur_r[pts[F.b].i]):
            oth = hm.edges[F.e1]
            conn = len(hm.faces) if up[oth] else oth
            face_uf.unite(i, conn)
        if not touch(h, pts[F.b], pts[F.c], cur_r[pts[F.b].i], cur_r[pts[F.c].i]):
            oth = hm.edges[F.e2]
            conn = len(hm.faces) if up[oth] else oth
            face_uf.unite(i, conn)
        if not touch(h, pts[F.a], pts[F.c], cur_r[pts[F.a].i], cur_r[pts[F.c].i]):
            oth = hm.edges[F.e3]
            conn = len(hm.faces) if up[oth] else oth
            face_uf.unite(i, conn)
        if not up[i]:
            st = Pt3(stx, sty, 0)
            nd = Pt3(ndx, ndy, 0)
            if st.in_triangle(pts[F.a], pts[F.b], pts[F.c]):
                st_face = i
            if nd.in_triangle(pts[F.a], pts[F.b], pts[F.c]):
                nd_face = i

    if not face_uf.united(st_face, nd_face):
        hi = md - 1
        brk = md
        continue

    lo = md

sys.stdout.write(str(brk))
sys.stdout.write("\n")
