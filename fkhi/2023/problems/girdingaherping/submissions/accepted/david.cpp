#pragma GCC optimize("O3,unroll-loops")
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<double>
#define ld double;
#define ii pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vc vector<char>
#define vs vector<string>
#define vd vector<double>
#define vcom vector<com>
#define vld vector<ld>
#define vll vector<ll>
#define vvi vector<vi>
#define vvii vector<vii>
#define vvc vector<vc>
#define vvs vector<vs>
#define vvll vector<vll>
#define vvd vector<vd>
#define vvcom vector<vcom>
#define vvld vector<vld>
#define FOR(x,n) for(int x=0;x<(n);x++)
#define FORS(x,n) for(int x=1;x<=(n);x++)
#define FORE(x,a) for(auto &x: a)
#define FORT(x,a,b) for(int x=(a);x<(b);x++)
#define FORD(x,a,b) for(int x=(a);x>=(b);x--)
#define ALL(x) x.begin(),x.end()
#define REP(n) for(int _ = 0; _ < n; _++)
#define MT make_tuple
#define MP make_pair
#define pb push_back
#define endl '\n'
#define F first
#define S second
#define vvvll vector<vvll>
#define sz(x) ((int)x.size())

using namespace std::chrono;

const double EPS = 1E-9;
int n;
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

struct seg {
    Point<double> p, q;
    int id;

    double get_y(double x) const {
        if (abs(p.x - q.x) < EPS)
            return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};

bool intersect1d(double l1, double r1, double l2, double r2) {
    if (l1 > r1)
        swap(l1, r1);
    if (l2 > r2)
        swap(l2, r2);
    return max(l1, l2) <= min(r1, r2) + EPS;
}

int vec(const Point<double>& a, const Point<double>& b, const Point<double>& c) {
    double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
}

bool intersect(const seg& a, const seg& b)
{
    if(abs(a.id-b.id) == 1 || (min(a.id,b.id) == 0 && max(a.id,b.id) == n-1)) return false;
    return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
           intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
           vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
           vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}

bool operator<(const seg& a, const seg& b)
{
    double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));

    if(a.get_y(x) < b.get_y(x) - EPS) return true;
    if(b.get_y(x) < a.get_y(x) - EPS) return false;

    return a.id < b.id;
}

struct event {
    double x;
    int tp, id;

    event() {}
    event(double x, int tp, int id) : x(x), tp(tp), id(id) {}

    bool operator<(const event& e) const {
        if (abs(x - e.x) > EPS)
            return x < e.x;
        return tp > e.tp;
    }
};

set<seg> s;
vector<set<seg>::iterator> where;

set<seg>::iterator prev(set<seg>::iterator it) {
    return it == s.begin() ? s.end() : --it;
}

set<seg>::iterator next(set<seg>::iterator it) {
    return ++it;
}

//microseconds f1,f2,f3;

bool has_intersect(const vector<seg>& a) {\
    int n = (int)a.size();
    vector<event> e(2*n);
    for (int i = 0; i < n; ++i) {
        e[2*i]=event(min(a[i].p.x, a[i].q.x), +1, i);
        e[2*i+1]=event(max(a[i].p.x, a[i].q.x), -1, i);
    }
    sort(e.begin(), e.end());
    s.clear();
    where.resize(a.size());
    int es = e.size();
    //auto s1 = high_resolution_clock::now();
    for (int i = 0; i < es; ++i) {
        int id = e[i].id;
        if (e[i].tp == +1) {
            set<seg>::iterator nxt = s.lower_bound(a[id]), prv = prev(nxt);
            if (nxt != s.end() && intersect(*nxt, a[id])){
                return true;
            }
            if (prv != s.end() && intersect(*prv, a[id])){
                return true;
            }
            where[id] = s.insert(nxt, a[id]);
        } else {
            set<seg>::iterator nxt = next(where[id]), prv = prev(where[id]);
            if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv)){
                return true;
            }
            s.erase(where[id]);
        }
    }

    return false;
}

template<class P>
P lineProj(P a, P b, P p, bool refl=false) {
	P v = b - a;
	return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

template<class T>
T polygonArea(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	FOR(i,sz(v)-1) a += v[i].cross(v[i+1]);
	return a/2;
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	FOR(i,n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}

pair<bool,double> calc(double m, vector<Point<double>> &h) {
    vector<seg> th;
    vector<Point<double>> tp;
    FOR(i,n) {
        Point<double> p1,q1,p2,q2,s1d,s2d;
        p1 = h[i];
        q1 = h[(i+1)%n];
        p2 = h[(i+1)%n];
        q2 = h[(i+2)%n];
        s1d = (q1-p1).perp().unit();
        s2d = (q2-p2).perp().unit();
        p1 = p1 + s1d*m;
        q1 = q1 + s1d*m;
        p2 = p2 + s2d*m;
        q2 = q2 + s2d*m;
        int r;
        Point<double> in;
        tie(r,in) = lineInter(p1,q1,p2,q2);
        //assert(r != 0);
        if(r == -1) {
            //assert((q1-p2).dist() <= EPS);
            in = q1;
        }
        tp.pb(in);
    }
    double a = polygonArea(tp);
    if(a < 0) return {true,a};

    Point<double> tt = (tp[1]+tp[0])/2 + (h[2]-h[1]).perp().unit()*1e-2;

    if(!inPolygon(tp,tt)) return {true,a};

    FOR(i,n) {
        th.pb({tp[i],tp[(i+1)%n],i});
    }
    bool res = has_intersect(th);
    
    
    return {res,a};
}


void solve() {
    cin >> n;
    vector<Point<double>> h(n);
    FOR(i,n) {
        cin >> h[i].x >> h[i].y;
    }

    double ta = polygonArea(h)/2;
    //cout << ina << endl;
    double l = 0, r = 2e9;

    cout << setprecision(12) << fixed;
    bool pos = false;
    while(abs(l-r) > 1e-10 && abs(l-r)/(l+EPS) > 1e-10) {
        double m = (l+r)/2;
        bool res;
        double a;

        tie(res,a) = calc(m,h);
        if(res || a < ta) {
            r = m;
            if(!res) pos = true;
        } else {
            l = m;
        }
    }
    if(pos) {
        cout  << l << endl;
    } else {
        cout << "Omogulegt!" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;

    while(t--) {
        solve();
    }
}
