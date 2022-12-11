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

ll *dist;
int *dad;
struct cmp {
  bool operator()(int a, int b) {
    return dist[a] != dist[b] ? dist[a] < dist[b] : a < b; }
};
pair<ll*, int*> dijkstra(int n, int s, vector<vii> adj) {
  dist = new ll[n];
  dad = new int[n];
  rep(i,0,n) dist[i] = DINF, dad[i] = -1;
  set<int, cmp> pq;
  dist[s] = 0, pq.insert(s);
  while (!pq.empty()) {
    int cur = *pq.begin(); pq.erase(pq.begin());
    rep(i,0,adj[cur].size()) {
      int nxt = adj[cur][i].first;
      ll ndist = dist[cur] + adj[cur][i].second;
      if (ndist < dist[nxt]) pq.erase(nxt),
        dist[nxt] = ndist, dad[nxt] = cur, pq.insert(nxt);
    } }
  return pair<ll*, int*>(dist, dad); }

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vii> adj(n+1);

    rep(i,0,k) {
        int x;
        cin >> x;
        adj[0].push_back(ii(x, 0));
    }

    rep(i,0,m) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[b].push_back(ii(a,c));
    }

    pair<ll*,int*> res = dijkstra(n+1, 0, adj);
    ll mx = 0;
    rep(i,1,n+1) {
        mx = max(mx, res.first[i]);
    }

    if (mx == DINF) {
        cout << "danger" << endl;
    } else {
        cout << mx << endl;
    }

    return 0;
}

