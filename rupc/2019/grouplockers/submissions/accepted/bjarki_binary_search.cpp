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

int arr[500000],
    pre[500000];

int main() {
    int n, m;
    cin >> n >> m;

    rep(i,0,m) {
        char c;
        cin >> c;
        arr[i] = c - '0';
        pre[i] = arr[i];
        if (i > 0) pre[i] += pre[i-1];
    }

    int mn = INF;
    rep(i,0,m) {
        int lo = i,
            hi = m-1,
            res = -1;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            int s = pre[mid];
            if (i > 0) s -= pre[i-1];
            if (s >= n) {
                res = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        if (res != -1) {
            mn = min(mn, res - i);
        }
    }

    if (mn == INF) {
        cout << "impossible" << endl;
    } else {
        cout << mn << endl;
    }

    return 0;
}

