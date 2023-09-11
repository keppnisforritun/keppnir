#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

int n, c, t;
int times[1'000'001];
int mem[1'000'000];
int dp(int i) {
    if (i == n) {
        return 0;
    }
    if (mem[i] != -1) {
        return mem[i];
    }
    int start = distance(times, lower_bound(times, times+n, times[i]+t));
    int end = min(start + c, n);
    int res = 0;
    for (int j = start; j < end; j++) {
        res = max(res, j - start + dp(j) + 1);
    }
    return mem[i] = res;
}

int main() {
    memset(mem, -1, sizeof(mem));
    cin >> n >> c >> t;
    
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    cout << dp(0) << endl;

    return 0;
}
