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

    ll cost = 0;
    while (pylsur >= 2) {
        cost += 549;
        pylsur -= 2;
        if (gos) gos -= 1;
    }

    while (pylsur >= 1 && gos >= 1) {
        cost += 499;
        pylsur -= 1;
        gos -= 1;
    }

    while (pylsur >= 1) {
        cost += 299;
        pylsur -= 1;
    }

    while (gos >= 1) {
        cost += 249;
        gos -= 1;
    }

    cout << cost << endl;

    return 0;
}

