#include<bits/stdc++.h>
using namespace std;
typedef complex<double> point;
typedef vector<point> polygon;
typedef pair<int,int> ii;
const double EPS = 1e-9;

bool xy_order(const point &p1, const point &p2) {
    if(real(p1) > real(p2)) return false;
    if(real(p1) < real(p2)) return true;
    if(imag(p1) > imag(p2)) return false;
    if(imag(p1) < imag(p2)) return true;
    return false;
}

double is_left(point p0, point p1, point p2) {
    return real(p1 - p0) * imag(p2 - p0) - real(p2 - p0) * imag(p1 - p0);
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
        if(abs(real(s1->lp - s1->rp)) < EPS && abs(real(s2->lp - s2->rp)) < EPS) {
            double a1 = imag(s1->lp), b1 = imag(s1->rp);
            if(a1 > b1) swap(a1, b1);
            double a2 = imag(s2->lp), b2 = imag(s2->rp);
            if(a2 > b2) swap(a2, b2);
            return (a1 < b2) && (a2 > b1);
        }
        double lsign = is_left(s1->lp, s1->rp, s2->lp);
        double rsign = is_left(s1->lp, s1->rp, s2->rp);
        if(lsign * rsign > 0.0) return false;
        lsign = is_left(s2->lp, s2->rp, s1->lp);
        rsign = is_left(s2->lp, s2->rp, s1->rp);
        if(lsign * rsign > 0.0) return false;
        return true;
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

point intersect(L(a,b), L(p,q)) {
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
    vector<double> ori;
    for(int i = 0; i < n; ++i) {
        ori.push_back(arg(p[i] - p[(i + 1) % n]));
    }
    double bst = abs(ori[0] - ori.back() - 2 * M_PI);
    double rot = (ori[0] + ori.back() + 2 * M_PI) / 2;
    for(int i = 1; i < n; ++i) {
        if(abs(ori[i] - ori[i - 1]) > bst) {
            bst = abs(ori[i] - ori[i - 1]);
            rot = (ori[i] + ori[i - 1]) / 2;
        }
    }
    for(int i = 0; i < n; ++i) {
        p[i] *= polar(1.0, rot);
    }
    int mnind = 0;
    for(int i = 1; i < n; ++i) {
        if(imag(p[i]) < imag(p[mnind])) mnind = i;
        else if(imag(p[i]) == imag(p[mnind]) && real(p[i]) > real(p[mnind])) mnind = i;
    }
    double l = 0, r = 2e9, a = polygon_area(p), mnrat = DBL_MAX; bool poss = false;
    while(r - l > 1e-7) {
        double m = (l + r) / 2.0;
        polygon q = contract(p, m);
        if(imag(q[(mnind + 1) % n]) < imag(q[mnind]) - EPS || imag(q[(mnind + n - 1) % n]) < imag(q[mnind]) - EPS) r = m;
        else if(!simple(q)) r = m;
        else if(polygon_area(q) > a / 2.0) l = m;
        else r = m, poss = true, mnrat = min(mnrat, polygon_area(q) / a);
    }
    if(!poss) cout << "Omogulegt!\n";
    else {
        assert(mnrat < 0.5 - 1e-5);
        cout << setprecision(15) << (l + r) / 2.0 << '\n';
    }
}
