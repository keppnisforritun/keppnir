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

int cost = 0,
    mn = INF;

void bt(int a, int b) {
    a = max(a, 0);
    b = max(b, 0);
    if (cost >= mn) {
        return;
    }

    if (a == 0 && b == 0) {
        mn = cost;
        return;
    }

    cost += 499;
    bt(a-1,b-1);
    cost -= 499;

    cost += 549;
    bt(a-2,b-1);
    cost -= 549;

    if (b > 0) {
        cost += 249;
        bt(a,b-1);
        cost -= 249;
    }

    if (a > 0) {
        cost += 299;
        bt(a-1,b);
        cost -= 299;
    }
}

int main() {
    int pylsur, gos;
    cin >> pylsur >> gos;

    bt(pylsur, gos);
    cout << mn << endl;

    return 0;
}

