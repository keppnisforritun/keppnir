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

int main() {
    int n;
    cin >> n;
    vii arr(n);
    rep(i,0,n) {
        cin >> arr[i].first >> arr[i].second;
    }

    vector<vi> adj(n+2);
    int NEG = n,
        POS = n+1;

    rep(i,0,n) {
        rep(j,i+1,n) {
            ll dx = arr[i].first - arr[j].first,
               dy = arr[i].second - arr[j].second,
               dmax = 40 + 50 + 40;

            if (dx*dx + dy*dy <= dmax*dmax) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    rep(i,0,n) {
        if (arr[i].second <= 40 + 50) {
            if (arr[i].first < 0) {
                adj[i].push_back(NEG);
                adj[NEG].push_back(i);
            } else {
                adj[i].push_back(POS);
                adj[POS].push_back(i);
            }
        }
    }

    vector<bool> vis(n+2);
    stack<int> S;
    S.push(POS);
    vis[POS] = true;

    while (!S.empty()) {
        int cur = S.top();
        S.pop();

        iter(it,adj[cur]) {
            if (!vis[*it]) {
                vis[*it] = true;
                S.push(*it);
            }
        }
    }

    if (vis[NEG]) {
        cout << "impossible" << endl;
    } else {
        cout << "possible" << endl;
    }

    return 0;
}

