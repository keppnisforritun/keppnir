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

int item[40];
int n, k;

vi adj[5010],
   radj[5010];
bool reach[5010][40],
     isitem[5010],
     hasvisited[5010];
int parent[5010];

vi path;

void traverse(int from, int to) {
    // cout << from+1 << " to " << to+1 << endl;

    memset(parent,-1,sizeof(parent));
    stack<int> S;
    S.push(from);
    parent[from] = from;
    while (!S.empty()) {
        int cur = S.top();
        S.pop();
        iter(it,adj[cur]) {
            if (parent[*it] == -1) {
                parent[*it] = cur;
                S.push(*it);
            }
        }
    }
    // cout << "here" << endl;
    assert(parent[to] != -1);
    S.push(to);
    while (S.top() != from) {
        S.push(parent[S.top()]);
    }
    S.pop();
    while (!S.empty()) {
        cout << S.top()+1 << endl;
        S.pop();
    }
}

void recon() {
    // cout << "path: ";
    // iter(it,path) {
    //     cout << *it+1 << " ";
    // }
    // cout << endl;

    cout << path[0]+1 << endl;
    rep(i,1,path.size()) {
        traverse(path[i-1], path[i]);
    }
}

void bt(int at) {
    if (!reach[at][k]) {
        return;
    }

    bool any = false;
    rep(i,0,k) {
        if (!hasvisited[item[i]]) {
            any = true;
            if (!reach[at][i]) {
                return;
            }
        }
    }

    if (!any) {
        path.push_back(n-1);
        recon();
        exit(0);
    }

    rep(i,0,k) {
        if (!hasvisited[item[i]]) {
            hasvisited[item[i]] = true;
            path.push_back(item[i]);
            bt(item[i]);
            path.pop_back();
            hasvisited[item[i]] = false;
        }
    }
}

int main() {
    int m;
    cin >> n >> m >> k;

    rep(i,0,k) {
        cin >> item[i];
        item[i]--;
        isitem[item[i]] = true;
    }

    rep(i,0,m) {
        int a, b;
        string state;
        cin >> a >> b >> state;
        a--, b--;
        adj[a].push_back(b);
        radj[b].push_back(a);
        if (state == "open") {
            adj[b].push_back(a);
            radj[a].push_back(b);
        }
    }

    item[k] = n-1;
    rep(i,0,k+1) {
        stack<int> S;
        reach[item[i]][i] = true;
        S.push(item[i]);
        while (!S.empty()) {
            int cur = S.top();
            S.pop();
            iter(it,radj[cur]) {
                if (!reach[*it][i]) {
                    reach[*it][i] = true;
                    S.push(*it);
                }
            }
        }
        // rep(j,0,n) {
        //     if (reach[j][i]) {
        //         cout << j+1 << " can reach " << item[i]+1 << endl;
        //     }
        // }
    }

    hasvisited[0] = true;
    path.push_back(0);
    bt(0);
    cout << "impossible" << endl;

    return 0;
}

