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

const double pi = acos(-1.0);

int main() {
    int n;
    cin >> n;

    double res = 0.0;
    rep(i,0,n) {
        int deg, r1, r2;
        cin >> deg >> r1 >> r2;

        if (abs(r1-r2) < 1e-9) continue;

        res += (deg / 360.0) * (pi * r2 * r2);
        res -= (deg / 360.0) * (pi * r1 * r1);
    }

    cout << round(res) << endl;

    return 0;
}

