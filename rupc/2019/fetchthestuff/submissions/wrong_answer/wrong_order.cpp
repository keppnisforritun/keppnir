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

void impossible() {
    cout << "impossible" << endl;
    exit(0);
}

vi adj[5010],
   before[40];
bool visited[40],
     inpath[40];
int parent[5010];
vi order;
void dfs(int at) {
    if (inpath[at]) {
        impossible();
    }
    if (visited[at]) {
        return;
    }

    visited[at] = true;
    inpath[at] = true;

    iter(it,before[at]) {
        dfs(*it);
    }

    order.push_back(at);
    inpath[at] = false;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vi items(k);
    rep(i,0,k) {
        cin >> items[i];
        items[i]--;
    }

    rep(i,0,m) {
        int a, b;
        string state;
        cin >> a >> b >> state;
        a--, b--;
        adj[a].push_back(b);
        if (state == "open") {
            adj[b].push_back(a);
        }
    }

    memset(parent,-1,sizeof(parent));
    queue<int> Q;
    parent[0] = 0;
    Q.push(0);
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        iter(it,adj[cur]) {
            if (parent[*it] == -1) {
                parent[*it] = cur;
                Q.push(*it);
            }
        }
    }
    rep(i,0,k) {
        if (parent[items[i]] == -1) {
            impossible();
        }
    }

    rep(i,0,k) {
        memset(parent,-1,sizeof(parent));
        Q.push(items[i]);
        parent[items[i]] = items[i];
        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            iter(it,adj[cur]) {
                if (parent[*it] == -1) {
                    parent[*it] = cur;
                    Q.push(*it);
                }
            }
        }
        if (parent[n-1] == -1) {
            impossible();
        }
        rep(j,0,k) {
            if (parent[items[j]] == -1) {
                before[i].push_back(j);
            }
        }
    }

    rep(i,0,k) {
        dfs(i);
    }

    cout << 1 << endl;
    rep(i,0,k) {
        cout << items[i]+1 << endl;
    }
    cout << n << endl;

    return 0;
}


