#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

int main() {
    int n;
    cin >> n;

    ll res = 0;
    rep(i,0,n) {
        ll deg, r1, r2;
        cin >> deg >> r1 >> r2;

        if (r1 == r2) continue;

        res += deg * r2 * r2;
        res -= deg * r1 * r1;
    }

    cout << setprecision(12) << res * 3.141592653589793 / 360.0 << endl;

    return 0;
}

