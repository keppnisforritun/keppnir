#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

int main()
{
    int n, c, t;
    cin >> n >> c >> t;
    
    vector<int> times(n);
    for (auto& x : times) {
        cin >> x;
    }

    vector<int> dp(n+1, 0);
    int start = n;
    int res = 0;
    for (int i = n-1; i >= 0; i--) {
        while (times[start-1] >= times[i] + t) start--;
        int end = min(start+c, n);
        for (int j = start; j < end; j++) {
            dp[i] = max(dp[i], j - start + dp[j] + 1);
        }
        res = max(res, dp[i]);
    }

    cout << res << endl;

    return 0;
}
