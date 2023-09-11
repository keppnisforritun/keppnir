#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, q, a, b; cin >> n >> q;
    vector<int> st(n);
    for(int i = 0; i < n; ++i)
        st[i] = i + 1;
    while(q--) {
        cin >> a >> b;
        a--; b--;
        for(int i = a; i <= b; ++i) st[i] = -st[i];
        reverse(st.begin() + a, st.begin() + b + 1);
    }
    for(int x : st) cout << x << ' ';
    cout << '\n';
}
