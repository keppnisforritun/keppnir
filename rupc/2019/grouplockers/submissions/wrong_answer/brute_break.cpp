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

int arr[500000];

int main() {
    cin.sync_with_stdio(false);
    clock_t start = clock();

    int n, m;
    cin >> n >> m;

    int tot = 0;
    rep(i,0,m) {
        char c;
        cin >> c;
        arr[i] = c - '0';
        tot += arr[i];
    }

    if (tot < n) {
        cout << "impossible" << endl;
        return 0;
    }

    int best = m;
    for (int i = 0; i < m && tot >= n; i++) {
        if ((i&0xff) == 0 && (clock() - start) * 1.0 / CLOCKS_PER_SEC > 0.98) {
            break;
        }
        if (arr[i] == 0) continue;

        int cur = 0;
        for (int j = i; j - i + 1 < best && j < m; j++) {
            cur += arr[j];
            if (cur >= n) {
                best = j - i + 1;
                break;
            }
        }

        tot -= arr[i];
    }

    cout << best-1 << endl;

    return 0;
}

