#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

bool ok(vi &v, vi &w) {
    int fix = INT_MAX;
    for(int i = 0; i < v.size(); ++i) {
        if(v[i] == w[i]) continue;
        if(fix == INT_MAX) fix = w[i] - v[i];
        else if(fix != w[i] - v[i]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, mx = 0; cin >> n;
    string s; cin >> s;
    vvi res;
    vi cnt(26, 0);
    res.push_back(cnt);
    for(int i = 0; i < n; ++i) {
        cnt[s[i] - 'a']++;
        for(int j = 0; j < res.size() && j <= i - mx; ++j) {
            if(ok(cnt, res[j])) {
                mx = max(mx, i - j + 1);
                break;
            }
        }
        res.push_back(cnt);
    }
    cout << mx << '\n';
}
