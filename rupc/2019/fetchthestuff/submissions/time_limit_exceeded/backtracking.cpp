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

vector<bool> curvisited;

vi path;
void bt(int at) {
    // cout << endl;
    // cout << "path: ";
    // iter(it,path) {
    //     cout << *it+1 << " ";
    // }
    // cout << endl;
    // cout << "hasvisited: ";
    // rep(i,0,n) cout << hasvisited[i];
    // cout << endl;
    // cout << "curvisited: ";
    // rep(i,0,n) cout << curvisited[i];
    // cout << endl;


    if (!reach[at][k]) {
// cout << "cant reach end" << endl;
        return;
    }

    bool any = false;
    rep(i,0,k) {
        if (!hasvisited[item[i]]) {
            any = true;
            if (!reach[at][i]) {
// cout << "cant reach " << item[i]+1 << endl;
                return;
            }
        }
    }

    if (!any && at == n-1) {
        iter(it,path) {
            cout << *it+1 << endl;
        }
        exit(0);
    }

    iter(it,adj[at]) {
        if (curvisited[*it]) continue;
        if (!hasvisited[*it] && isitem[*it]) {
            vector<bool> nxt(n);
            nxt.swap(curvisited);
            curvisited[*it] = true;
            hasvisited[*it] = true;
            path.push_back(*it);
            bt(*it);
            path.pop_back();
            hasvisited[*it] = false;
            curvisited[*it] = false;
            nxt.swap(curvisited);
        } else {
            bool first = !hasvisited[*it];
            curvisited[*it] = true;
            hasvisited[*it] = true;
            path.push_back(*it);
            bt(*it);
            path.pop_back();
            if (first) hasvisited[*it] = false;
            curvisited[*it] = false;
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

            // cout << cur+1 << " can reach " << item[i]+1 << endl;

            iter(it,radj[cur]) {
                if (!reach[*it][i]) {
                    reach[*it][i] = true;
                    S.push(*it);
                }
            }
        }
    }

    curvisited = vector<bool>(n);
    path.push_back(0);
    bt(0);
    cout << "impossible" << endl;

    return 0;
}

