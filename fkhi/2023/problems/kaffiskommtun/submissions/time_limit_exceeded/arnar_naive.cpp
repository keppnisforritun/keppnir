#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

int main()
{
    ios_base::sync_with_stdio(false);

    int n, c, t;
    cin >> n >> c >> t;
    
    vector<int> times(n);
    for (auto& x : times) {
        cin >> x;
    }

    vector<int> dp(n+1, 0);
    int res = 0;
    for (int i = n-1; i >= 0; i--) {
        int start = i+1;
        while (start < n && times[start] < times[i]+t) start++;
        int end = min(start+c, n);
        for (int j = start; j < end; j++) {
            dp[i] = max(dp[i], j - start + dp[j] + 1);
        }
        res = max(res, dp[i]);
    }

    cout << res << endl;

    return 0;
}
