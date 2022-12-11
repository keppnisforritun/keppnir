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

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    rep(i,0,n) dist[i] = INF;

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> S;
    rep(i,0,k) {
         int x;
         cin >> x;
         x--;
         dist[x] = 0;
         S.push(make_pair(dist[x], x));
    }

    vector<vii> adj(n);

    rep(i,0,m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[b].push_back(ii(a,c));
    }

    while (!S.empty()) {
        int cur = S.top().second;
        ll curd = S.top().first;
        S.pop();
        if (curd != dist[cur]) {
            continue;
        }

        iter(it,adj[cur]) {
            int nxt = it->first;
            ll ndist = dist[cur] + it->second;
            if (ndist < dist[nxt]) {
                dist[nxt] = ndist;
                S.push(make_pair(dist[nxt], nxt));
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

