#include<bits/stdc++.h>
using namespace std;
typedef complex<double> point;
typedef vector<point> polygon;
typedef pair<int,int> ii;
const double EPS = 1e-9;

#define P(p) const point &p
#define L(p0, p1) P(p0), P(p1)
double dot(P(a), P(b)) { return real(conj(a) * b); }
double cross(P(a), P(b)) { return imag(conj(a) * b); }
double ccw(P(a), P(b), P(c)) { return cross(b - a, c - b); }

bool parallel(L(a, b), L(p, q)) {
  return abs(cross(b - a, q - p)) < EPS; }

bool collinear(L(a, b), L(p, q)) {
  return abs(ccw(a, b, p)) < EPS && abs(ccw(a, b, q)) < EPS; }

point normalize(P(p), double k = 1.0) {
  return abs(p) == 0 ? point(0,0) : p / abs(p) * k; }

double polygon_area(polygon &p) {
    double area = 0;
    for(int i = 1; i < p.size() - 1; ++i)
        area += cross(p[i] - p[0], p[i + 1] - p[0]);
    return abs(area / 2);
}

bool intersect(L(a,b), L(p,q), point &res,
    bool lseg=false, bool rseg=false) {
  // NOTE: check parallel/collinear before
  point r = b - a, s = q - p;
  double c = cross(r, s),
         t = cross(p - a, s) / c, u = cross(p - a, r) / c;
  if (lseg && (t < 0-EPS || t > 1+EPS)) return false;
  if (rseg && (u < 0-EPS || u > 1+EPS)) return false;
  res = a + t * r; return true; }

double progress(P(p), L(a, b)) {
  if (abs(real(a) - real(b)) < EPS)
    return (imag(p) - imag(a)) / (imag(b) - imag(a));
  else return (real(p) - real(a)) / (real(b) - real(a)); }

bool line_segment_intersect(L(a, b), L(c, d), point &A,
                                              point &B) {
  if (abs(a - b) < EPS && abs(c - d) < EPS) {
    A = B = a; return abs(a - d) < EPS; }
  else if (abs(a - b) < EPS) {
    A = B = a; double p = progress(a, c,d);
    return 0.0 <= p && p <= 1.0
      && (abs(a - c) + abs(d - a) - abs(d - c)) < EPS; }
  else if (abs(c - d) < EPS) {
    A = B = c; double p = progress(c, a,b);
    return 0.0 <= p && p <= 1.0
      && (abs(c - a) + abs(b - c) - abs(b - a)) < EPS; }
  else if (collinear(a,b, c,d)) {
    double ap = progress(a, c,d), bp = progress(b, c,d);
    if (ap > bp) swap(ap, bp);
    if (bp < 0.0 || ap > 1.0) return false;
    A = c + max(ap, 0.0) * (d - c);
    B = c + min(bp, 1.0) * (d - c);
    return true; }
  else if (parallel(a,b, c,d)) return false;
  else if (intersect(a,b, c,d, A, true,true)) {
    B = A; return true; }
  return false; }

point push(point a, point b, point c, double d) {
    point v1 = normalize((b - a) * 1i, d);
    point v2 = normalize((c - b) * 1i, d);
    point res;
    assert(intersect(a + v1, b + v1, b + v2, c + v2, res));
    return res;
}

polygon contract(polygon &p, double d) {
    int n = p.size();
    polygon q(n);
    for(int i = 0; i < n; ++i)
        q[i] = push(p[(i + n - 1) % n], p[i], p[(i + 1) % n], d);
    return q;
}

bool simple(polygon &p) {
    int n = p.size();
    point res1, res2;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 2; j < n; ++j) {
            if(i == 0 && j == n - 1) continue;
            if(line_segment_intersect(p[i], p[(i + 1) % n], p[j], p[(j + 1) % n], res1, res2))
                return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; 
    cin >> n;
    polygon p;
    double x, y;
    for(int i = 0; i < n; ++i) {
        cin >> x >> y;
        if(p.size() >= 2 && collinear(p[p.size() - 2], p.back(), p.back(), point(x, y))) p.pop_back();
        p.push_back(point(x, y));
    }
    if(collinear(p[0], p.back(), p.back(), p[p.size() - 2])) p.pop_back();
    n = p.size(); int mnind = 0;
    for(int i = 1; i < n; ++i) {
        if(imag(p[i]) < imag(p[mnind])) mnind = i;
        else if(imag(p[i]) == imag(p[mnind]) && real(p[i]) > real(p[mnind])) mnind = i;
    }
    double l = 0, r = 2e9, a = polygon_area(p); bool poss = false;
    while(r - l > 1e-6 && (r - l) / (l + EPS) > 1e-6) {
        double m = (l + r) / 2.0;
        polygon q = contract(p, m);
        if(imag(q[(mnind + 1) % n]) < imag(q[mnind]) - EPS || imag(q[(mnind + n - 1) % n]) < imag(q[mnind]) - EPS) r = m;
        else if(!simple(q)) r = m;
        else if(polygon_area(q) > a / 2.0) l = m;
        else r = m, poss = true;
    }
    if(!poss) cout << "Omogulegt!\n";
    else cout << setprecision(15) << (l + r) / 2.0 << '\n';
}
