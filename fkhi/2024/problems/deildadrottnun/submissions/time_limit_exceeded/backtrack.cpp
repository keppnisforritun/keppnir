#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

bool backtrack(ll left, vi &cur) {
    if(left == 0) return true;
    if(left < 0) return false;
    int nxt = cur.size() + 1;
    cur.push_back(nxt);
    if(backtrack(left - nxt, cur)) return true;
    cur.back()++;
    if(backtrack(left - nxt - 1, cur)) return true;
    cur.pop_back();
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    ll n; cin >> n;
    vector<int> ans;
    backtrack(n, ans);
    cout << ans.size() << '\n';
    for(int x : ans) cout << x << ' ';
    cout << '\n';
}
    
