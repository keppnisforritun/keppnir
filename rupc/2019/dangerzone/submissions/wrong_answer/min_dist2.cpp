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

    vii arr(n);
    rep(i,0,n) {
        cin >> arr[i].first >> arr[i].second;
    }

    bool ok = true;
    rep(i,0,n) {
        rep(j,0,n) {
            if (i == j) continue;

            ll dx = arr[i].first - arr[j].first,
               dy = arr[i].second - arr[j].second,
               dmax = 40 + 50 + 50;

            if (dx*dy + dy*dy < dmax*dmax) {
                ok = false;
            }
        }
    }

    rep(i,0,n) {
        if (arr[i].second < 40 + 50) {
            ok = false;
        }
    }

    if (ok) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}

