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

    int left = 0;
    rep(i,0,n) {
        int x;
        cin >> x;
        left += x;
    }

    int right = 0;
    rep(i,0,m) {
        int x;
        cin >> x;
        right += x;
    }

    if (left == right) {
        cout << "either" << endl;
    } else if (left < right) {
        cout << "left" << endl;
    } else {
        assert(right < left);
        cout << "right" << endl;
    }

    return 0;
}

