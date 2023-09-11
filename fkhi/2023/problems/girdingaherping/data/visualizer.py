#!/usr/bin/python3
import math
import sys
from PIL import Image, ImageDraw

EPS = 1e-9

def sgn(x):
    return -1 if x < 0 else 1


class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        return f"Point({self.x:.6f}, {self.y:.6f})"

    def __getitem__(self, i):
        return self.x if i == 0 else self.y
    
    def __iter__(self):
        yield self.x
        yield self.y

    def __len__(self):
        return 2

    def __add__(self, other):
        if other == 0:
            return self
        return Point(self.x + other.x, self.y + other.y)

    def __radd__(self, other):
        return self + other

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        if isinstance(other, (int, float)):
            return Point(self.x * other, self.y * other)
        if isinstance(other, Point):
            return self.x * other.x + self.y * other.y
        return NotImplemented

    def __rmul__(self, other):
        return self * other
    
    def __truediv__(self, other):
        if isinstance(other, (int, float)):
            return Point(self.x / other, self.y / other)
        return NotImplemented

    def dot(self, other):
        return self * other

    def cross(self, other):
        return self.x * other.y - self.y * other.x

    def ccw(self, a, b):
        return (a - self).cross(b - a)

    def collinear(self, a, b):
        return abs(self.ccw(a, b)) < EPS

    def length_squared(self):
        return self.dot(self)

    def length(self):
        return self.length_squared() ** 0.5

    def norm(self):
        return self / self.length()

    def perp(self):
        return Point(-self.y, self.x)
    

class Line:
    def __init__(self, a, b, segment=True):
        self.a = a
        self.b = b
        self.segment = segment
    
    def __getitem__(self, i):
        return self.a if i == 0 else self.b

    def __iter__(self):
        yield self.a
        yield self.b

    def __len__(self):
        return 2

    def progress(self, p):
        return (p - self.a) / (self.b - self.a)

    def __contains__(self, p):
        return p.collinear(self.a, self.b) and (not self.segment or -EPS < self.progress(p) < 1+EPS)

    def vec(self):
        return self.b - self.a

    def shift(self, p):
        return Line(self.a + p, self.b + p, self.segment)

    def __repr__(self):
        return f"Line({self.a}, {self.b}, {self.segment})"

    def intersection(self, other):
        r = self.vec()
        s = other.vec()
        c = r.cross(s)
        t = (other.a - self.a).cross(s) / c
        u = (other.a - self.a).cross(r) / c
        return self.a + t * r


def contract(poly, m):
    edges = [Line(poly[i-1], poly[i], segment=False) for i in range(len(poly))]
    shifted = [e.shift(e.vec().norm().perp()*m) for e in edges]
    inters = [shifted[i-1].intersection(shifted[i]) for i in range(len(poly))]
    return inters

if __name__ == "__main__":
    filename = sys.argv[1]
    ansfile = sys.argv[2]

    m = "Omogulegt!"
    with open(ansfile, 'r') as f:
        try:
            m = float(f.readline())
        except ValueError:
            pass

    n = int(input())

    poly = []
    for _ in range(n):
        poly.append(Point(*map(float, input().split())))
        if len(poly) > 2 and poly[-3].collinear(poly[-2], poly[-1]):
            poly.pop(-2)
    if poly[-2].collinear(poly[-1], poly[0]):
        poly.pop(-1)
    n = len(poly)

    IMAGE_WIDTH, IMAGE_HEIGHT = 5000, 5000
    PADDING = 2
    VERTEX_RADIUS = 3
    
    O = sum(poly) * (1/n)
    poly = [p - O for p in poly]

    min_x = min(poly, key=lambda p: p.x).x
    max_x = max(poly, key=lambda p: p.x).x
    min_y = min(poly, key=lambda p: p.y).y
    max_y = max(poly, key=lambda p: p.y).y

    BASE = 1.1
    EXP = -20

    while True:
        LEFT = -BASE**EXP
        RIGHT = BASE**EXP
        TOP = -BASE**EXP
        BOTTOM = BASE**EXP
        PADDING = BASE**EXP * 0.001
        
        if LEFT <= min_x - PADDING and max_x + PADDING <= RIGHT and TOP <= min_y - PADDING and max_y + PADDING <= BOTTOM:
            break
        EXP += 1
    
    def morph(p):
        if isinstance(p, Point):
           return Point((p.x - LEFT) * IMAGE_WIDTH / (RIGHT - LEFT),
                     (p.y - TOP) * IMAGE_HEIGHT / (BOTTOM - TOP))
        return Line(morph(p.a), morph(p.b), p.segment)

    def draw_point(draw, p, color):
        tx = p.x
        ty = p.y
        sx = tx - VERTEX_RADIUS
        sy = ty - VERTEX_RADIUS
        ex = tx + VERTEX_RADIUS
        ey = ty + VERTEX_RADIUS
        draw.ellipse((sx, sy, ex, ey), fill=color, outline="black")
    
    def draw_edge(draw, e, color):
        draw.line([tuple(e.a), tuple(e.b)], fill=color, width=2)

    background = [(0, 0), (IMAGE_WIDTH, IMAGE_HEIGHT)]
      
    # creating new Image object
    img = Image.new("RGBA", (IMAGE_WIDTH, IMAGE_HEIGHT))

    # create rectangle image
    draw = ImageDraw.Draw(img)
    draw.rectangle(background, fill="black")

    for i in range(n):
        draw_edge(draw, morph(Line(poly[i-1], poly[i])), "white")
    
    if m != "Omogulegt!":
        contracted = contract(poly, m)
        for i in range(n):
            draw_edge(draw, morph(Line(contracted[i-1], contracted[i])), "red")


    overlay = Image.new('RGBA', img.size, (0,0,0,0,))
    overlay_draw = ImageDraw.Draw(overlay)

    img = Image.alpha_composite(img, overlay)
    img = img.convert("RGB")
    img.save(filename, 'PNG')
