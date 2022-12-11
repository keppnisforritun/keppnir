#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 1000000000;

template <class T> int Size(const T &x) { return x.size(); }

struct union_find {
  vi p; union_find(int n = 0) : p(n, -1) { }
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool unite(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp) return false;
    if (p[xp] > p[yp]) swap(xp,yp);
    p[xp] += p[yp], p[yp] = xp;
    return true; }
  int size(int x) { return -p[find(x)]; } };

vector<bool> visited;
vi order;
void scc_dfs(const vvi &adj, int u) {
  int v; visited[u] = true;
  rep(i,0,Size(adj[u]))
    if (!visited[v = adj[u][i]]) scc_dfs(adj, v);
  order.push_back(u); }


vi adj[5010];
pair<union_find, vi> scc(int n) {
  int u, v;
  order.clear();
  union_find uf(n); vi dag; vvi rev(n);
  rep(i,0,n) rep(j,0,Size(adj[i])) rev[adj[i][j]].push_back(i);
  visited.resize(n);
  fill(visited.begin(), visited.end(), false);
  rep(i,0,n) if (!visited[i]) scc_dfs(rev, i);
  fill(visited.begin(), visited.end(), false);
  stack<int> S;
  for (int i = n-1; i >= 0; i--) {
    if (visited[order[i]]) continue;
    S.push(order[i]), dag.push_back(order[i]);
    while (!S.empty()) {
      visited[u = S.top()] = true, S.pop();
      uf.unite(u, order[i]);
      rep(j,0,Size(adj[u]))
        if (!visited[v = adj[u][j]]) S.push(v); } }
  return pair<union_find, vi>(uf, dag); }

set<int> items;
union_find uf;
vi comp[5010];
set<int> cadj[5010];
int n;
map<int,int> mem;

int dp(int cur) {
    if (mem.find(cur) != mem.end()) {
        return mem[cur];
    }

    int here = 0;
    iter(it,comp[cur]) {
        if (items.find(*it) != items.end()) {
            here++;
        }
    }

    if (uf.find(n-1) == cur) {
        return mem[cur] = here;
    }

    int mx = -INF;
    iter(it,cadj[cur]) {
        mx = max(mx, here + dp(*it));
    }

    return mem[cur] = mx;
}

void travel(int at, int nxt) {
    map<int, int> par;
    stack<int> S;
    S.push(at);
    par[at] = -1;
    while (!S.empty()) {
        int cur = S.top();
        S.pop();
        iter(it,adj[cur]) {
            if (par.find(*it) == par.end()) {
                par[*it] = cur;
                S.push(*it);
            }
        }
    }
    assert(par.find(nxt) != par.end());
    vi path;
    int tmp = nxt;
    while (tmp != at) {
        path.push_back(tmp);
        tmp = par[tmp];
    }
    reverse(path.begin(), path.end());
    iter(it,path) {
        cout << *it+1 << endl;
    }
}

void reconstruct(int cur, int last) {
    int here = 0;
    iter(it,comp[cur]) {
        if (items.find(*it) != items.end()) {
            here++;
            travel(last, *it);
            last = *it;
        }
    }

    if (uf.find(n-1) == cur) {
        travel(last, n-1);
        return;
    }

    int mx = dp(cur);
    iter(it,cadj[cur]) {
        if (mx == here + dp(*it)) {
            reconstruct(*it, last);
            return;
        }
    }
    assert(false);
}

int main() {
    int m, k;
    cin >> n >> m >> k;

    rep(i,0,k) {
        int x;
        cin >> x;
        x--;
        items.insert(x);
    }

    rep(i,0,m) {
        int a, b;
        string s;
        cin >> a >> b >> s;
        a--, b--;
        adj[a].push_back(b);
        if (s != "locked") {
            adj[b].push_back(a);
        }
    }

    pair<union_find, vi> res = scc(n);
    uf = res.first;
    rep(i,0,n) {
        comp[uf.find(i)].push_back(i);
        iter(it,adj[i]) {
            if (uf.find(i) != uf.find(*it)) {
                cadj[uf.find(i)].insert(uf.find(*it));
            }
        }
    }

    if (dp(uf.find(0)) != k) {
        cout << "impossible" << endl;
        return 0;
    }

    cout << 1 << endl;
    reconstruct(uf.find(0), 0);

    return 0;
}

