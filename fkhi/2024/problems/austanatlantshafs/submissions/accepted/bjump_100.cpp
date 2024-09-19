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

int get_jump(vvi &bjump, int i, int h) {
    for(int k = 19; k >= 0; --k) {
        if(!(h & (1 << k))) continue;
        i = bjump[k][i];
    }
    return i;
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
    vvi bjump(20, vi(n, -1));
    for(int i = 0; i < n; ++i)
        bjump[0][i] = ind[par[i]];
    for(int k = 1; k < 20; ++k)
        for(int i = 0; i < n; ++i)
            bjump[k][i] = bjump[k - 1][bjump[k - 1][i]];
    for(int i = 0; i < n; ++i) {
        if(xs[i] == -1) continue;
        int h = 0;
        for(int k = 19; k >= 0; --k) {
            int j = get_jump(bjump, i, h | (1 << k));
            if(high[j].second > 1) continue;
            if(high[j].first > xs[i]) continue;
            h |= 1 << k;
        }
        int j = get_jump(bjump, i, h);
        cout << names[j] << '\n';
    }
}
