#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

template <class T>
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }

ll n, m;
int node_count{ 0 }, edge_count{ 0 };
ll scale{ 1 };

vector<ll> val;
vector<int> proxy;
vector<vector<int>> in_edges;
vector<vector<int>> out_edges;

int new_node(ll x = 0) {
    val.emplace_back(x);
    in_edges.emplace_back();
    out_edges.emplace_back();
    proxy.emplace_back(node_count);
    return node_count++;
}

int most_recent_node() {
    return node_count - 1;
}

void add_edge(int a, int b) {
    edge_count++;
    in_edges[b].push_back(a);
    out_edges[a].push_back(b);
}

void add_proxy_if_needed(int i) {
    if (!in_edges[proxy[i]].empty()) {
        int new_proxy = new_node();
        add_edge(new_proxy, proxy[i]);
        proxy[i] = new_proxy;
    }
}

int find_sink(int missing_at_least) {
    for (int i = n; i < n+m; i++) {
        if (val[i] + missing_at_least <= n) {
            return i;
        }
    }
    return -1;
}

void connect_to_sink(int u) {
    auto sink = find_sink(val[u]);
    if (sink != -1) {
        add_proxy_if_needed(sink);
        add_edge(u, proxy[sink]);
        val[sink] += val[u];
        return;
    }
    int v = new_node();
    val[v] += val[u]/2;
    add_edge(u, v);
    int w = new_node();
    val[w] += val[u]/2;
    add_edge(u, w);
    connect_to_sink(v);
    connect_to_sink(w);
}

void make(int initial, ll denom) {
    ll pow2 = 1;
    ll e = 0;
    while (pow2 <= denom) pow2 *= 2, e += 1;

    ll diff = pow2 - denom;
    
    int next_u = initial;
    val[initial] = scale * denom;
    for (ll i = e-1; i >= 0; i--) {
        int u = next_u, v, w;
        v = new_node();
        add_edge(u, v);
        val[v] += scale << i;
        if (diff & (1 << i)) {
            add_proxy_if_needed(initial);
            w = proxy[initial];
            val[w] += scale << i;
            add_edge(u, w);
        }
        else {
            w = new_node();
            val[w] += scale << i;
            add_edge(u, w);
            connect_to_sink(w);
        }
        next_u = v;
    }
    connect_to_sink(next_u);
}


struct union_find {
  vector<int> p;
  union_find(int n) : p(n, -1) { }
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool unite(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp) return false;
    p[xp] += p[yp], p[yp] = xp;
    return true; }
  int size(int x) { return -p[find(x)]; } };

int main()
{
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    
    ll denom = m;
    while (denom % 2 == 0) denom /= 2, scale *= 2;

    for (int i = 0; i < n+m; i++) {
        new_node();
    }

    for (int i = 0; i < n; i++) {
        make(i, denom);
    }

    union_find uf(node_count);
    for (int i = 0; i < node_count; i++) {
        if (out_edges[i].size() == 1 && in_edges[i].size() == 1) {
            uf.unite(out_edges[i][0], i);
        }
    }
    
    map<int, int> mapping;
    for (int i = 0; i < node_count; i++) {
        int j = uf.find(i);
        if (mapping.find(j) == mapping.end()) {
            mapping[j] = mapping.size();
        }
    }

    int new_node_count = static_cast<int>(mapping.size());
    vector<vector<int>> new_out(new_node_count);
    int new_edge_count = 0;
    for (int i = 0; i < node_count; i++) {
        int a = mapping[uf.find(i)];
        for (auto j : out_edges[i]) {
            int b = mapping[uf.find(j)];
            if (a != b) {
                new_out[a].push_back(b);
                new_edge_count++;
            }
        }

    }

    cout << new_node_count << " " << new_edge_count << endl;
    for (int i = 0; i < new_node_count; i++) {
        for (auto j : new_out[i]) {
            cout << i+1 << " " << j+1 << endl;
        }
    }

    return 0;
}
