#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int main() {
    ios_base::sync_with_stdio(false);
    int n, mx = 0; cin >> n;
    string s; cin >> s;
    for(int msk = 2; msk < (1 << 26); ++msk) {
        if(__builtin_popcount(msk) < 2) continue;
        int least = msk & ~(msk - 1);
        vector<pair<vi,int>> res;
        vi cnt(26, 0); 
        res.push_back(make_pair(cnt, -1));
        for(int i = 0; i < n; ++i) {
            int k = s[i] - 'a';
            if(least & (1 << k)) {
                for(int j = 0; j < 26; ++j) {
                    if(least & (1 << j)) continue;
                    if(!(msk & (1 << j))) continue;
                    cnt[j]--;
                }
            } else {
                cnt[s[i] - 'a']++;
            }
            res.push_back(make_pair(cnt, i));
        }
        sort(res.begin(), res.end());
        for(int i = 0; i <= n; ++i) {
            int j = i + 1;
            while(j <= n && res[i].first == res[j].first) j++;
            j--;
            mx = max(mx, res[j].second - res[i].second);
            i = j;
        }
    }
    cout << mx << '\n';
}
