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
    int pylsur, gos;
    cin >> pylsur >> gos;

    int mn = INF;
    for (int k = 0; k <= max(pylsur, gos); k++) {
        int cost = k * 549,
            curpylsur = max(0, pylsur - 2 * k),
            curgos = max(0, gos - k);

        int t = min(curpylsur, curgos);
        cost += t * 499;
        curpylsur -= t;
        curgos -= t;

        cost += curpylsur * 299;
        cost += curgos * 249;

        mn = min(mn, cost);
    }

    cout << mn << endl;

    return 0;
}

