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

bool is_end[200000];
map<int,ll> dist;

struct cmp {
    bool operator()(const int &a, const int &b) {
        ll x = dist.find(a) == dist.end() ? INF : dist[a];
        ll y = dist.find(b) == dist.end() ? INF : dist[b];

        if (x != y) {
            return x < y;
        }
        return a < b;
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;


    rep(i,0,k) {
         int x;
         cin >> x;
         x--;
         is_end[x] = true;
    }

    vector<vii> adj(n);

    rep(i,0,m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back(ii(b,c));
    }

    ll mx = 0;
    rep(start,0,n) {
        dist.clear();
        set<int, cmp> S;
        dist[start] = 0;
        S.insert(start);

        ll best = INF;
        while (!S.empty()) {
            int cur = *S.begin();
            S.erase(S.begin());

            if (is_end[cur]) {
                best = dist[cur];
                break;
            }

            iter(it,adj[cur]) {
                int nxt = it->first;
                ll ndist = dist[cur] + it->second;
                if (dist.find(nxt) == dist.end() || ndist < dist[nxt]) {
                    S.erase(nxt);
                    dist[nxt] = ndist;
                    S.insert(nxt);
                }
            }
        }

        mx = max(mx, best);
    }

    if (mx == INF) {
        cout << "danger" << endl;
    } else {
        cout << mx << endl;
    }

    return 0;
}

