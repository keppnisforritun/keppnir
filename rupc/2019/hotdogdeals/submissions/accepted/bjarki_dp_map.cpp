#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 1000000000;

map<ii,int> mem;

int dp(int a, int b) {
    a = max(0, a);
    b = max(0, b);

    if (a == 0 && b == 0) {
        return 0;
    }

    ii st(a,b);
    if (mem.find(st) != mem.end())
        return mem[st];

    int mn = INF;

    if (b > 0) mn = min(mn, 249 + dp(a,b-1));
    if (a > 0) mn = min(mn, 299 + dp(a-1,b));
    mn = min(mn, 499 + dp(a-1,b-1));
    mn = min(mn, 549 + dp(a-2,b-1));

    return mem[st] = mn;
}

int main() {
    int pylsur, gos;
    cin >> pylsur >> gos;

    cout << dp(pylsur, gos) << endl;

    return 0;
}

