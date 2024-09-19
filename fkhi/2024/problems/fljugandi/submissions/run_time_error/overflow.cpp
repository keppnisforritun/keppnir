#pragma GCC optimize("Ofast","unroll-loops")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)

struct unionfind {
  vi p;
  unionfind(int n) : p(n, -1) { }
  int find(int x) {
    return p[x] < 0 ? x : p[x] = find(p[x]);
  }
  bool united(int x, int y) {
    return find(x) == find(y);
  }
  void unite(int x, int y) {
    int a = find(x), b = find(y);
    if(a == b) return;
    if(p[a] > p[b]) swap(a, b);
    p[a] += p[b];
    p[b] = a;
    return;
  }
};

struct bigpt3 {
    ll x, y, z;
    bigpt3(ll a, ll b, ll c) :
        x(a), y(b), z(c) { }
    bool iszero() {
        return x == 0 && y == 0 && z == 0;
    }
};

struct pt3 {
    ll x, y, z; int i = -1;
    pt3(ll x = 0, ll y = 0, ll z = 0) : x(x), y(y), z(z) {}
    pt3 operator +(const pt3 &o) const {
        return pt3(x + o.x, y + o.y, z + o.z);
    }
    pt3 operator -(const pt3 &o) const {
        return pt3(x - o.x, y - o.y, z - o.z);
    }
    bigpt3 cross(const pt3 &o) const {
        ll a = x, b = y, c = z;
        return bigpt3(
            b * o.z - c * o.y,
            c * o.x - a * o.z,
            a * o.y - b * o.x
        );
    }
    ll dot(const pt3 &o) const {
        ll dx = x; dx *= o.x;
        ll dy = y; dy *= o.y;
        ll dz = z; dz *= o.z;
        return dx + dy + dz;
    }
    ll bigdot(const bigpt3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
    bool iszero() {
        return x == 0 && y == 0 && z == 0;
    }
    ll sign(pt3 p2, pt3 p3) {
        return (*this - p3).x * (p2 - p3).y -
            (p2 - p3).x * (*this - p3).y;
    }
    bool in_triangle(pt3 p1, pt3 p2, pt3 p3) {
        ll d1 = sign(p1, p2);
        ll d2 = sign(p2, p3);
        ll d3 = sign(p3, p1);

        bool has_neg = d1 < 0 || d2 < 0 || d3 < 0;
        bool has_pos = d1 > 0 || d2 > 0 || d3 > 0;

        return !(has_neg && has_pos);
    }
};

struct face {
    int a, b, c;
    bigpt3 q;
    int e1, e2, e3;
    vi points;
    int dead = 1e9;
    face(int a, int b, int c, bigpt3 q) : a(a), b(b), c(c), q(q), e1(-1), e2(-1), e3(-1) { }
};

struct hullmaker {

    vector<face> faces;
    vector<int> edges;

    void glue(int F1, int F2, int &e1, int &e2) {
        e1 = edges.size();
        edges.push_back(F2);
        e2 = edges.size();
        edges.push_back(F1);
    }

    void prepare(vector<pt3> &p) {
        mt19937 rng(1337);
        int n = p.size();
        shuffle(p.begin(), p.end(), rng);
        vi ve = { 0 };
        for(int i = 1; i < n; ++i) {
            if(ve.size() == 1) {
                if(!(p[ve[0]] - p[i]).iszero())
                    ve.push_back(i);
            } else if(ve.size() == 2) {
                if(!(p[ve[1]] - p[ve[0]]).cross(p[i] - p[ve[0]]).iszero()) ve.push_back(i);
            } else if((p[i] - p[ve[0]]).bigdot((p[ve[1]] - p[ve[0]]).cross(p[ve[2]] - p[ve[0]])) != 0) {
                ve.push_back(i);
                break;
            }
        }
        assert(ve.size() == 4);
        for(int i = 0; i < ve.size(); ++i)
            swap(p[i], p[ve[i]]);
    }

    vi hull3(vector<pt3> &p) {
        int n = p.size();
        vector<int> f, new_face(n, -1);
        prepare(p);
        vector<vector<int>> conflict(n);
        for(int i = 0; i < n; ++i)
            conflict[i].reserve(100);
        auto add_face = [&](int a, int b, int c) {
            int F = faces.size();
            faces.emplace_back(a, b, c, (p[b] - p[a]).cross(p[c] - p[a]));
            f.push_back(F);
            return F;
        };
        int F1 = add_face(0, 1, 2);
        int F2 = add_face(0, 2, 1);
        glue(F1, F2, faces[F1].e1, faces[F2].e3);
        glue(F1, F2, faces[F1].e2, faces[F2].e2);
        glue(F1, F2, faces[F1].e3, faces[F2].e1);
        for(int i = 3; i < n; ++i) {
            for(int F : { F1, F2 }) {
                ll Q = (p[i] - p[faces[F].a]).bigdot(faces[F].q);
                if(Q >= 0) {
                    conflict[i].push_back(F);
                    faces[F].points.push_back(i);
                }
            }
        }
        for(int i = 3; i < n; ++i) {
            for(int F : conflict[i])
                faces[F].dead = min(faces[F].dead, i);
            int v = -1;
            conflict[i].erase(remove_if(conflict[i].begin(), conflict[i].end(), [&](int k) {
                return faces[k].dead != i;
            }), conflict[i].end());
            for(int F : conflict[i]) {
                int parr[3] = { faces[F].a, faces[F].b, faces[F].c };
                int earr[3] = { faces[F].e1, faces[F].e2, faces[F].e3 };
                for(int j = 0; j < 3; ++j) {
                    int j2 = j == 2 ? 0 : j + 1;
                    if(faces[edges[earr[j]]].dead > i) {
                        int Fn = new_face[parr[j]] = add_face(parr[j], parr[j2], i);
                        faces[Fn].points.reserve(faces[Fn].points.size() + faces[F].points.size() + faces[edges[earr[j]]].points.size());
                        set_union(faces[F].points.begin(), faces[F].points.end(), faces[edges[earr[j]]].points.begin(), faces[edges[earr[j]]].points.end(), back_inserter(faces[Fn].points));
                        faces[Fn].points.erase(remove_if(faces[Fn].points.begin(), faces[Fn].points.end(), [&](int k) {
                            return k <= i || (p[k] - p[faces[Fn].a]).bigdot(faces[Fn].q) <= 0;
                        }), faces[Fn].points.end());
                        for(int k : faces[Fn].points)
                            conflict[k].push_back(Fn);
                        edges[earr[j] ^ 1] = Fn;
                        faces[Fn].e1 = earr[j];
                        v = parr[j];
                    }
                }
            }
            if(v == -1) continue;
            while(faces[new_face[v]].e2 == -1) {
                int u = faces[new_face[v]].b;
                glue(new_face[v], new_face[u], faces[new_face[v]].e2, faces[new_face[u]].e3);
                v = u;
            }
        }
        f.erase(remove_if(f.begin(), f.end(), [&](int F) {
            return faces[F].dead < n;
        }), f.end());
        return f;
    }
};

bool touch(ll h, pt3 a, pt3 b, ll ra, ll rb) {
    if(h >= ra || h >= rb) return false;
    ll ra2 = ra * ra - h * h, rb2 = rb * rb - h * h;
    ll dx = a.x - b.x, dy = a.y - b.y;
    ll nrm = dx * dx + dy * dy;
    ll rhs = nrm - ra2 - rb2;
    if(rhs < 0) return true;
    return 4 * ra2 * rb2 > rhs * rhs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, m; ll h;
    cin >> n >> h;
    vector<ll> xs(n), ys(n);
    int stx, sty, ndx, ndy;
    cin >> stx >> sty;
    cin >> ndx >> ndy;
    for(int i = 0; i < n; ++i)
        cin >> xs[i] >> ys[i];
    cin >> m;
    vector<int> js(m), rs(m);
    for(int i = 0; i < m; ++i)
        cin >> js[i] >> rs[i], js[i]--;
    int lo = 0, hi = m, brk = -1;
    while(hi > lo) {
        int md = hi - (hi - lo) / 2;
        vector<pt3> pts;
        vector<ll> cur_r(n + 1, 0);
        bool ins = false;
        for(int i = 0; i < md; ++i)
            cur_r[js[i]] = max(cur_r[js[i]], (ll) rs[i]);
        for(int i = 0; i < n; ++i) {
            if(cur_r[i] == 0) continue;
            pts.emplace_back(xs[i], ys[i], xs[i] * xs[i] + ys[i] * ys[i] - cur_r[i] * cur_r[i] + h * h);
            pts.back().i = i;
            if(cur_r[i] > h) {
                ll dx1 = xs[i] - stx, dy1 = ys[i] - sty;
                ll dx2 = xs[i] - ndx, dy2 = ys[i] - ndy;
                ll n1 = dx1 * dx1 + dy1 * dy1;
                ll n2 = dx2 * dx2 + dy2 * dy2;
                ll rsq = (cur_r[i] - h) * (cur_r[i] - h);
                if(n1 < rsq || n2 < rsq)
                    ins = true;
            }
        }
        if(ins) {
            hi = md - 1;
            brk = md;
            continue;
        } else if(pts.size() < 4) {
            lo = md;
            continue;
        }
        pts.emplace_back(0, 0, 1e18);
        pts.back().i = n;
        hullmaker hm;
        vi res = hm.hull3(pts);
        int st_face = hm.faces.size(), nd_face = hm.faces.size();
        unionfind face_uf(hm.faces.size() + 1);
        vector<bool> up(hm.faces.size(), true);
        for(int i : res) {
            face F = hm.faces[i];
            pt3 X = pts[F.b] - pts[F.a];
            pt3 Y = pts[F.c] - pts[F.a];
            ll Z = X.x * Y.y - X.y * Y.x;
            up[i] = Z >= 0;
        }
        for(int i : res) {
            face F = hm.faces[i];
            if(!touch(h, pts[F.a], pts[F.b], cur_r[pts[F.a].i], cur_r[pts[F.b].i])) {
                int oth = hm.edges[F.e1];
                int conn = up[oth] ? hm.faces.size() : oth;
                face_uf.unite(i, conn);
            }
            if(!touch(h, pts[F.b], pts[F.c], cur_r[pts[F.b].i], cur_r[pts[F.c].i])) {
                int oth = hm.edges[F.e2];
                int conn = up[oth] ? hm.faces.size() : oth;
                face_uf.unite(i, conn);
            }
            if(!touch(h, pts[F.a], pts[F.c], cur_r[pts[F.a].i], cur_r[pts[F.c].i])) {
                int oth = hm.edges[F.e3];
                int conn = up[oth] ? hm.faces.size() : oth;
                face_uf.unite(i, conn);
            }
            if(!up[i]) {
                pt3 st(stx, sty, 0), nd(ndx, ndy, 0);
                if(st.in_triangle(pts[F.a], pts[F.b], pts[F.c]))
                    st_face = i;
                if(nd.in_triangle(pts[F.a], pts[F.b], pts[F.c]))
                    nd_face = i;
            }
        }
        if(face_uf.find(st_face) != face_uf.find(nd_face)) {
            hi = md - 1;
            brk = md;
            continue;
        }
        lo = md;
    }
    cout << brk << '\n';
}
