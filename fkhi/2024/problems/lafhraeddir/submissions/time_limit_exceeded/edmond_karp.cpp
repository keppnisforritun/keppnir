#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const ll INF = ~(1LL<<63);
typedef vector<int> vi;
typedef vector<vi> vvi;

#define MAXV 2000
ll q[MAXV], p[MAXV], d[MAXV];
struct flow_network {
  struct edge { ll v, nxt, cap;
    edge(ll _v, ll _cap, ll _nxt)
      : v(_v), nxt(_nxt), cap(_cap) { } };
  ll n, *head; vector<edge> e, e_store;
  flow_network(ll _n) : n(_n) {
    memset(head = new ll[n], -1, n*sizeof(ll)); }
  void reset() { e = e_store; }
  void add_edge(ll u, ll v, ll uv, ll vu=0) {
    e.push_back(edge(v,uv,head[u])); head[u]=((ll)e.size())-1;
    e.push_back(edge(u,vu,head[v])); head[v]=((ll)e.size())-1;}
  ll max_flow(ll s, ll t, bool res=true) {
    e_store = e;
    ll l, r, v, f = 0;
    while (true) {
      memset(d, -1, n*sizeof(ll));
      memset(p, -1, n*sizeof(ll));
      l = r = 0, d[q[r++] = s] = 0;
      while (l < r)
        for (ll u = q[l++], i = head[u]; i != -1; i=e[i].nxt)
          if (e[i].cap > 0 &&
              (d[v = e[i].v] == -1 || d[u] + 1 < d[v]))
            d[v] = d[u] + 1, p[q[r++] = v] = i;
      if (p[t] == -1) break;
      ll at = p[t], x = INF;
      while (at != -1)
        x = min(x, e[at].cap), at = p[e[at^1].v];
      at = p[t], f += x;
      while (at != -1)
        e[at].cap -= x, e[at^1].cap += x, at = p[e[at^1].v]; }
    if (res) reset();
    return f; } };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int L, E; cin >> L >> E;
    vector<string> aname(E), dname(L);
    map<string,int> aind;
    vl acnt(E), astr(E), dcnt(L), dstr(L);
    vvi immune(L, vi(E, 0));
    for(int i = 0; i < E; ++i) {
        cin >> aname[i] >> astr[i] >> acnt[i];
        aind[aname[i]] = i;
    }
    for(int i = 0; i < L; ++i) {
        cin >> dname[i] >> dstr[i] >> dcnt[i];
        int k; cin >> k;
        for(int j = 0; j < k; ++j) {
            string cur; cin >> cur;
            immune[i][aind[cur]] = 1;
        }
    }
    ll lo = 0, hi = 1'000'000'000'000;
    while(hi > lo) {
        ll md = hi - (hi - lo) / 2;
        flow_network fw(E + L + 2);
        for(int i = 0; i < E; ++i) {
            fw.add_edge(E + L, i, acnt[i]);
        }
        __int128_t targ = 0;
        for(int i = 0; i < L; ++i) {
            targ += ((__int128_t) md) * dcnt[i];
            if(targ > E * 1'000'000'000LL) break;
            fw.add_edge(E + i, E + L + 1, md * dcnt[i]);
        }
        if(targ > E * 1'000'000'000LL) {
            hi = md - 1;
            continue;
        }
        for(int i = 0; i < L; ++i) {
            for(int j = 0; j < E; ++j) {
                if(immune[i][j]) continue;
                if(astr[j] < dstr[i]) continue;
                fw.add_edge(j, E + i, INF);
            }
        }
        if(fw.max_flow(E + L, E + L + 1) < targ)
            hi = md - 1;
        else lo = md;
    }
    cout << lo << '\n';
}

