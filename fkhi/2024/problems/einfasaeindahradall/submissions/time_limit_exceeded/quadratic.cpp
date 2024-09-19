#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, p, q; cin >> n;
    vi l(n), r(n);
    for(int i = 0; i < n; ++i)
        cin >> l[i] >> r[i];
    cin >> p;
    vvi particles(p, vi(n));
    for(int j = 0; j < p; ++j)
        for(int i = 0; i < n; ++i)
            cin >> particles[j][i];
    cin >> q;
    while(q--) {
        vi a(n), b(n);
        for(int i = 0; i < n; ++i)
            cin >> a[i] >> b[i];
        int cnt = 0;
        for(int j = 0; j < p; ++j) {
            bool ins = true;
            for(int i = 0; i < n; ++i) {
                ins &= particles[j][i] >= a[i];
                ins &= particles[j][i] <= b[i];
            }
            if(ins) cnt++;
        }
        cout << cnt << '\n';
    }
}

