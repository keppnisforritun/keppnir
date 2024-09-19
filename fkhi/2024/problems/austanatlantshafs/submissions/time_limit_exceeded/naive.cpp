#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

ii dfs_max(vvi &ch, int s, vi &xs) {
    ii ret(xs[s], s);
    for(int y : ch[s]) {
        ii sub = dfs_max(ch, y, xs);
        if(sub.first > ret.first) {
            ret = sub;
        } else if(sub.first == ret.first) {
            ret.second = -1;
        }
    }
    return ret;
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
    vvi ch(n); vi xs(n);
    map<string,int> ind;
    vector<string> names(n), par(n);
    for(int i = 0; i < n; ++i) {
        cin >> names[i] >> par[i] >> xs[i];
        ind[names[i]] = i;
    }
    for(int i = 1; i < n; ++i) {
        ch[ind[par[i]]].push_back(i);
    }
    vi ans(n);
    for(int i = 0; i < n; ++i) ans[i] = -1;
    queue<int> q;
    q.push(0);
    while(q.size() > 0) {
        int cur = q.front();
        q.pop();
        for(int z : ch[cur])
            q.push(z);
        ii high = dfs_max(ch, cur, xs);
        int j = high.second;
        if(j == -1) continue;
        if(ans[j] == -1)
            ans[j] = cur;
    }
    for(int i = 0; i < n; ++i) {
        if(xs[i] == -1) continue;
        cout << names[ans[i]] << '\n';
    }
}
