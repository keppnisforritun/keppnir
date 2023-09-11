#include<bits/stdc++.h>
using namespace std;
typedef complex<double> point;
typedef vector<point> polygon;
typedef pair<int,int> ii;
const double EPS = 1e-9;

bool xy_order(const point &p1, const point &p2) {
    return real(p1) < real(p2) - EPS || (abs(real(p1 - p2)) < EPS && imag(p1) > imag(p2) + EPS);
}

double is_left(point p0, point p1, point p2) {
    return real(p0 - p2) * imag(p1 - p2) - real(p1 - p2) * imag(p0 - p2);
}

struct event {
    int edge, type;
    point ev;
    event() : edge(-1), type(-1), ev(point()) { }
};

bool operator!=(const event &e1, const event &e2) {
    return (e1.edge != e2.edge) || (e1.type != e2.type) || (e1.ev != e2.ev);
}

bool operator<(const event &e1, const event &e2) {
    return xy_order(e1.ev, e2.ev);
}

struct event_queue {
    int ne, ix;
    vector<event> dat;

    event_queue(polygon &p) {
        ix = 0;
        ne = 2 * p.size();
        dat = vector<event>(ne);
        for(int i = 0; i < ((int) p.size()); ++i) {
            dat[2 * i].edge = i;
            dat[2 * i + 1].edge = i;
            dat[2 * i].ev = p[i];
            dat[2 * i + 1].ev = p[(i + 1) % p.size()];
            if(xy_order(p[i], dat[2 * i + 1].ev)) {
                dat[2 * i].type = 0;
                dat[2 * i + 1].type = 1;
            } else {
                dat[2 * i].type = 1;
                dat[2 * i + 1].type = 0;
            }
        }
        sort(dat.begin(), dat.end());
    }

    event next() {
        return ix >= ne ? event() : dat[ix++];
    }
};

struct line {
    double a, b, c;

    line() {}
    line(point p, point q) {
        a = imag(p) - imag(q);
        b = real(q) - real(p);
        c = -a * real(p) - b * imag(p);
        norm();
    }

    void norm() {
        double z = sqrt(a * a + b * b);
        if(abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    double dist(point p) const { return a * real(p) + b * imag(p) + c; }
};

inline bool betw(double l, double r, double x) {
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d) {
    if(a > b) swap(a, b);
    if(c > d) swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

bool intersect_2d(point a, point b, point c, point d, point &left, point &right) {
    if(!intersect_1d(real(a), real(b), real(c), real(d))) return false;
    if(!intersect_1d(imag(a), imag(b), imag(c), imag(d))) return false;
    line m(a, b);
    line n(c, d);
    double zn = m.a * n.b - m.b * n.a;
    if(abs(zn) < EPS) {
        if(abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS) return false;
        if(xy_order(b, a)) swap(a, b);
        if(xy_order(d, c)) swap(c, d);
        left = xy_order(a, c) ? c : a;
        right = xy_order(b, d) ? b : d;
        return true;
    } else {
        left = point(-(m.c * n.b - m.b * n.c) / zn, -(m.a * n.c - m.c * n.a) / zn);
        right = left;
        return betw(real(a), real(b), real(left)) && betw(imag(a), imag(b), imag(left)) &&
               betw(real(c), real(d), real(left)) && betw(imag(c), imag(d), imag(left));
    }
}

typedef struct sl_seg sl_seg;

struct sl_seg {
    int edge;
    point lp, rp;
    mutable set<struct sl_seg>::iterator above, below;
};

bool operator<(const sl_seg &a, const sl_seg &b) {
    return a.edge < b.edge;
}

struct sweep_line {
    int nv;
    polygon pn;
    set<sl_seg> tree;

    sweep_line(polygon &p) {
        nv = p.size();
        pn = p;
        tree = set<sl_seg>();
    }
    
    set<sl_seg>::iterator add(event &e) {
        sl_seg s;
        s.edge = e.edge;
        point v1 = pn[s.edge];
        point v2 = pn[(s.edge + 1) % pn.size()];
        if(xy_order(v1, v2)) {
            s.lp = v1;
            s.rp = v2;
        } else {
            s.rp = v1;
            s.lp = v2;
        }
        s.above = tree.end();
        s.below = tree.end();
        auto it = tree.insert(s).first;
        auto nxt = it, prv = it; 
        ++nxt;
        if(nxt != tree.end()) {
            it->above = nxt;
            nxt->below = it;
        }
        if(prv != tree.begin()) {
            prv--;
            it->below = prv;
            prv->above = it;
        }
        return it;
    }

    set<sl_seg>::iterator find(event &e) {
        sl_seg s;
        s.edge = e.edge;
        return tree.find(s);
    }

    void remove(set<sl_seg>::iterator s) {
        if(s == tree.end()) return;
        auto nxt = s; nxt++;
        if(nxt != tree.end()) {
            nxt->below = s->below;
        }
        auto prv = s;
        if(prv != tree.begin()) {
            prv--;
            prv->above = s->above;
        }
        tree.erase(s);
    }

    bool intersect(set<sl_seg>::iterator s1, set<sl_seg>::iterator s2) {
        if(s1 == tree.end() || s2 == tree.end()) return false;
        int e1 = s1->edge, e2 = s2->edge;
        if(((e1 + 1) % nv == e2) || (e1 == (e2 + 1) % nv)) return false;
        point jnk1, jnk2, a = s1->lp, b = s1->rp, c = s2->lp, d = s2->rp;
        return intersect_2d(a, b, c, d, jnk1, jnk2);
    }
};

bool simple(polygon &p) {
    event_queue eq(p);
    sweep_line sl(p);
    event e; 
    set<sl_seg>::iterator s;
    while((e = eq.next()) != event()) {
        if(e.type == 0) {
            s = sl.add(e);
            if(sl.intersect(s, s->above)) return false;
            if(sl.intersect(s, s->below)) return false;
        } else {
            s = sl.find(e);
            if(sl.intersect(s->above, s->below)) return false;
            sl.remove(s);
        }
    }
    return true;
}

#define P(p) const point &p
#define L(p0, p1) P(p0), P(p1)
double dot(P(a), P(b)) { return real(conj(a) * b); }
double cross(P(a), P(b)) { return imag(conj(a) * b); }
double ccw(P(a), P(b), P(c)) { return cross(b - a, c - b); }

bool collinear(L(a, b), L(p, q)) {
  return abs(ccw(a, b, p)) < EPS && abs(ccw(a, b, q)) < EPS; }

point normalize(P(p), double k = 1.0) {
  return abs(p) == 0 ? point(0,0) : p / abs(p) * k; }

double polygon_area(polygon &p) {
    double area = 0;
    for(int i = 1; i < ((int) p.size()) - 1; ++i)
        area += cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;
}

point intersect(point a, point b, point p, point q) {
  point r = b - a, s = q - p;
  double c = cross(r, s),
         t = cross(p - a, s) / c;
  return a + t * r; }

point push(point a, point b, point c, double d) {
    point v1 = normalize((b - a) * 1i, d);
    point v2 = normalize((c - b) * 1i, d);
    return intersect(a + v1, b + v1, b + v2, c + v2);
}

polygon contract(polygon &p, double d) {
    int n = p.size();
    polygon q(n);
    for(int i = 0; i < n; ++i)
        q[i] = push(p[(i + n - 1) % n], p[i], p[(i + 1) % n], d);
    return q;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; 
    cin >> n;
    polygon p;
    double x, y;
    for(int i = 0; i < n; ++i) {
        cin >> x >> y;
        p.push_back(point(x, y));
    }
    int mnind = 0;
    for(int i = 1; i < n; ++i) {
        if(imag(p[i]) < imag(p[mnind])) mnind = i;
        else if(imag(p[i]) == imag(p[mnind]) && real(p[i]) > real(p[mnind])) mnind = i;
    }
    double l = 0, r = 2e9, a = polygon_area(p); bool poss = false;
    while(r - l > 1e-7) {
        double m = (l + r) / 2.0;
        polygon q = contract(p, m);
        double new_a = polygon_area(q);
        if(imag(q[(mnind + 1) % n]) < imag(q[mnind]) - EPS || imag(q[(mnind + n - 1) % n]) < imag(q[mnind]) - EPS) r = m,
            cerr << "INV" << endl;
        else if(new_a < 0.0) r = m,
            cerr << "NEG" << endl;
        else if(!simple(q)) r = m,
            cerr << "NONSIMPLE" << endl;
        else if(new_a > a / 2.0) l = m,
            cerr << "TOOBIG" << endl;
        else r = m, poss = true,
            cerr << "OK" << endl;
    }
    if(!poss) cout << "Omogulegt!\n";
    else cout << setprecision(15) << (l + r) / 2.0 << '\n';
}
