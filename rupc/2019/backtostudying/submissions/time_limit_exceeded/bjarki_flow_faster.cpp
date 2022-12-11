#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;
const ll DINF = 1000000000000000000LL;

#define MAXV 400100
int q[MAXV];
ll d[MAXV];
struct flow_network {
  struct edge { int v, nxt; ll cap;
    edge(int _v, ll _cap, int _nxt)
      : v(_v), nxt(_nxt), cap(_cap) { } };
  int n, *head, *curh; vector<edge> e, e_store;
  flow_network(int _n) : n(_n) {
    curh = new int[n];
    memset(head = new int[n], -1, n*sizeof(int)); }
  void reset() { e = e_store; }
  void add_edge(int u, int v, ll uv, ll vu=0) {
    e.push_back(edge(v,uv,head[u])); head[u]=(int)e.size()-1;
    e.push_back(edge(u,vu,head[v])); head[v]=(int)e.size()-1;}
  ll augment(int v, int t, ll f) {
    if (v == t) return f;
    ll ret;
    for (int &i = curh[v]; i != -1; i = e[i].nxt)
      if (e[i].cap > 0 && d[e[i].v] + 1 == d[v])
        if ((ret = augment(e[i].v, t, min(f, e[i].cap))) > 0)
          return (e[i].cap -= ret, e[i^1].cap += ret, ret);
    return 0; }
  ll max_flow(int s, int t, bool res=true) {
    e_store = e;
    int l, r; ll f = 0, x;
    while (true) {
      memset(d, -1, n*sizeof(ll));
      l = r = 0, d[q[r++] = t] = 0;
      while (l < r)
        for (int v = q[l++], i = head[v]; i != -1; i=e[i].nxt)
          if (e[i^1].cap > 0 && d[e[i].v] == -1)
            d[q[r++] = e[i].v] = d[v]+1;
      if (d[s] == -1) break;
      memcpy(curh, head, n * sizeof(int));
      while ((x = augment(s, t, DINF)) != 0) f += x; }
    if (res) reset();
    return f; } };

int main() {
    int n;
    cin >> n;
    vii arr(n);
    ll tot = 0;
    rep(i,0,n) {
        cin >> arr[i].first >> arr[i].second;
        tot += arr[i].second;
    }

    sort(arr.begin(), arr.end());

    int lo = 0,
        hi = arr[0].first,
        res = -1;

    while (lo <= hi) {
        int mid = (lo+hi)/2;

        int SOURCE = 0,
            SINK = 1,
            EXAM = 2,
            PER = EXAM + n,
            CNT = PER + n;

        flow_network G(CNT);
        rep(i,0,n) {
            G.add_edge(SOURCE, EXAM + i, arr[i].second);
        }

        rep(i,0,n) {
            G.add_edge(EXAM + i, PER + i, DINF);
            if (i > 0) {
                G.add_edge(EXAM + i, EXAM + i - 1, DINF);
            }
        }

        rep(i,0,n) {
            ll len = arr[i].first;
            if (i == 0) {
                len -= mid;
            } else {
                len -= arr[i-1].first;
                len--;
                len = max(0LL, len);
            }
            assert(len >= 0);
            G.add_edge(PER + i, SINK, len);
        }

        if (G.max_flow(SOURCE, SINK) == tot) {
            res = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    if (res == -1) {
        cout << "impossible" << endl;
    } else {
        cout << res << endl;
    }

    return 0;
}

