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

    srand(time(NULL));

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
    for (int it = 0; ; it++) {
        if ((it&0xff) == 0 && (clock() - start) * 1.0 / CLOCKS_PER_SEC > 0.98) {
            break;
        }

        int i = rand() % m,
            cnt = 0;
        while (i < m && arr[i] == 0) i++;
        int sm = 0;
        while (i < m && sm < n && cnt < best) {
            cnt++;
            sm += arr[i++];
        }
        if (sm >= n) {
            best = min(best, cnt);
        }
    }

    cout << best-1 << endl;

    return 0;
}

