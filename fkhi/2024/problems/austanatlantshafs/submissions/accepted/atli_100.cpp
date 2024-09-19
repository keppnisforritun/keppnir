#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;

ii dfs(vvi &ch, int s, vi &high, vi &xs) {
    if(ch[s].empty()) {
        high[s] = s;
        return ii(xs[s], s);
    }
    ii mx(-1, -1);
    for(int y : ch[s]) {
        ii sub = dfs(ch, y, high, xs);
        if(sub.first > mx.first) mx = sub;
        else if(sub.first == mx.first) mx.second = -1;
    }
    if(mx.second != -1)
        high[mx.second] = s;
    return mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    if(n == 1) { cout << "jord\n"; return 0; }
    vvi g(n); vi xs(n);
    map<string,int> ind;
    vector<string> names(n), par(n);
    for(int i = 0; i < n; ++i) {
        cin >> names[i] >> par[i] >> xs[i];
        ind[names[i]] = i;
    }
    for(int i = 1; i < n; ++i) {
        g[ind[par[i]]].push_back(i);
    }
    vi ans(n);
    dfs(g, 0, ans, xs);
    for(int i = 0; i < n; ++i) {
        if(xs[i] == -1) continue;
        cout << names[ans[i]] << '\n';
    }
}
