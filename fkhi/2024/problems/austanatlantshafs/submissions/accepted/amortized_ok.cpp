#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

void dfs(vvi &ch, int s, vii &high, vi &xs) {
    high[s] = ii(xs[s], 1);
    for(int y : ch[s]) {
        dfs(ch, y, high, xs);
        if(high[y].first > high[s].first) {
            high[s] = high[y];
        } else if(high[y].first == high[s].first) {
            high[s].second += high[y].second;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
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
    vii high(n);
    dfs(g, 0, high, xs);
    for(int i = 0; i < n; ++i) {
        if(xs[i] == -1) continue;
        int j = i;
        while(true) {
            int k = ind[par[j]];
            if(k == j) break;
            if(high[k].second > 1) break;
            if(high[k].first > high[i].first) break;
            j = k;
        }
        cout << names[j] << '\n';
    }
}
