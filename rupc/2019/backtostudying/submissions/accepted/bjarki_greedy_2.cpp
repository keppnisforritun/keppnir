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

bool cmp(ii a, ii b) {
    if (a.first != b.first) {
        return a.first > b.first;
    }
    if (a.second != b.second) {
        // Does not matter
        return a.second > b.second;
    }
    return false;
}

int main() {
    int n;
    cin >> n;

    vii arr(n);
    rep(i,0,n) {
        cin >> arr[i].first >> arr[i].second;
    }

    sort(arr.begin(), arr.end(), cmp);

    int last_exam = arr[0].first;
    ll need = 0;
    for (int i = 0; i < arr.size(); i++) {
        int cur_exam = arr[i].first,
            cur_count = arr[i].second;

        need -= max(0, last_exam - cur_exam - 1);
        need = max(0LL, need);

        need += cur_count;
        last_exam = cur_exam;
    }

    need -= last_exam;

    if (need > 0) {
        cout << "impossible" << endl;
    } else {
        cout << -need << endl;
    }

    return 0;
}

