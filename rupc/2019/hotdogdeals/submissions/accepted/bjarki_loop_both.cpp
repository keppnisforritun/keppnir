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
    for (int i = 0; i <= max(pylsur, gos); i++) {
        for (int j = 0; j <= max(pylsur, gos); j++) {
            int a = max(0, pylsur - 2 * i - j),
                b = max(0, gos - i - j);
            mn = min(mn, i * 549 + j * 499 + a * 299 + b * 249);
        }
    }

    cout << mn << endl;

    return 0;
}

