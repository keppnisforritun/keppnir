#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    ll n; cin >> n;
    vector<int> ans; int cur = 1;
    while(n >= cur) {
        ans.push_back(cur);
        n -= cur;
        cur++;
    }
    for(int i = ans.size() - 1; n > 0; --i, --n)
        ans[i]++;
    cout << ans.size() << '\n';
    for(int x : ans) cout << x << ' ';
    cout << '\n';
}
    
