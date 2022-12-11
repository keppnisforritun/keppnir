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
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    int mn = INF,
        cur = 0,
        end = -1;
    for (int start = 0; start < m; start++) {
        while (cur < n && end+1 < m) {
            cur += s[++end] - '0';
        }

        if (cur >= n) {
            mn = min(mn, end - start);
        }

        cur -= s[start] - '0';
    }

    if (mn == INF) {
        cout << "impossible" << endl;
    } else {
        cout << mn << endl;
    }

    return 0;
}

