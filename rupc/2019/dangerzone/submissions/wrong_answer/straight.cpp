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
    bool left = true,
         right = true,
         up = true;
    rep(i,0,n) {
        int x, y;
        cin >> x >> y;
        if (y < 40+50) {
            if (x < 0) {
                left = false;
            } else {
                right = false;
            }
        }
        if (abs(x) < 40+25) {
            up = false;
        }
    }

    if (left || right || up) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}

