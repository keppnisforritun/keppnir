#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, p, q; cin >> n;
    vi l(n), r(n);
    for(int i = 0; i < n; ++i)
        cin >> l[i] >> r[i];
    vi coeff(n, 1);
    for(int i = 1; i < n; ++i)
        coeff[i] = coeff[i - 1],
        coeff[i] *= r[i - 1] - l[i - 1] + 1;
    int opts = coeff.back() * (r.back() - l.back() + 1);
    vi counts(opts, 0);
    cin >> p;
    while(p--) {
        int coord = 0, x;
        for(int i = 0; i < n; ++i) {
            cin >> x;
            coord += coeff[i] * (x - l[i]);
        }
        counts[coord]++;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = coeff[i]; j < opts; ++j) {
            int coord = j;
            if(i != n - 1) coord %= coeff[i + 1];
            if(coord >= coeff[i])
                counts[j] += counts[j - coeff[i]];
        }
    }
    cin >> q;
    while(q--) {
        vi a(n), b(n);
        bool ok = true;
        for(int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
            a[i] = max(a[i], l[i]);
            b[i] = min(b[i], r[i]);
            if(a[i] > r[i]) ok = false;
            if(b[i] < l[i]) ok = false;
        }
        if(!ok) {
            cout << 0 << '\n';
            continue;
        }
        for(int i = 0; i < n; ++i) {
            a[i] = (a[i] - l[i] - 1) * coeff[i];
            b[i] = (b[i] - l[i]) * coeff[i];
        }
        int cur = 0, neg = 0, ev = 0;
        for(int i = 0; i < n; ++i)
            cur += b[i];
        int res = counts[cur];
        for(int it = 1; it < (1 << n); ++it) {
            int msk = it ^ (it >> 1);
            ev = !ev;
            int diff = msk ^ (it - 1) ^ ((it - 1) >> 1);
            int togg = 31 - __builtin_clz(diff);
            if(msk & (1 << togg)) {
                neg += a[togg] < 0;
                cur += a[togg];
                cur -= b[togg];
            } else {
                neg -= a[togg] < 0;
                cur -= a[togg];
                cur += b[togg];
            }
            if(neg == 0) {
                if(ev) res -= counts[cur];
                else res += counts[cur];
            }
        }
        cout << res << '\n';
    }
}
