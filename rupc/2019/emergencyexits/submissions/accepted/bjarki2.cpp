#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const ll INF = 1000000000000000000LL;

ll dist[200000];

struct cmp {
    bool operator()(const int &a, const int &b) {
        if (dist[a] != dist[b]) {
            return dist[a] < dist[b];
        }
        return a < b;
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    rep(i,0,n) dist[i] = INF;

    set<int, cmp> S;
    rep(i,0,k) {
         int x;
         cin >> x;
         x--;
         dist[x] = 0;
         S.insert(x);
    }

    vector<vii> adj(n);

    rep(i,0,m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[b].push_back(ii(a,c));
    }

    while (!S.empty()) {
        int cur = *S.begin();
        S.erase(S.begin());

        iter(it,adj[cur]) {
            int nxt = it->first;
            ll ndist = dist[cur] + it->second;
            if (ndist < dist[nxt]) {
                S.erase(nxt);
                dist[nxt] = ndist;
                S.insert(nxt);
            }
        }
    }

    ll mx = 0;
    rep(i,0,n) {
        mx = max(mx, dist[i]);
    }

    if (mx == INF) {
        cout << "danger" << endl;
    } else {
        cout << mx << endl;
    }

    return 0;
}

