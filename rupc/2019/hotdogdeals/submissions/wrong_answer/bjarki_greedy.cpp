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

    int cost = 0;

    int k = min(pylsur / 2, gos);
    cost += 549 * k;
    pylsur -= k * 2;
    gos -= k;

    k = min(pylsur, gos);
    cost += 499 * k;
    pylsur -= k;
    gos -= k;

    k = pylsur;
    cost += 299 * k;
    pylsur -= k;

    k = gos;
    cost += 249 * k;
    gos -= k;

    assert(pylsur == 0 && gos == 0);
    cout << cost << endl;

    return 0;
}

