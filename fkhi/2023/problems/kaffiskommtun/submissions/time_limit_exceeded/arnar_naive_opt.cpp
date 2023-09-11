#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }


void readn(register int *n) {
  int sign = 1;
  register char c;
  *n = 0;
  while((c = getc_unlocked(stdin)) != '\n') {
    switch(c) {
      case '-': sign = -1; break;
      case ' ': goto hell;
      case '\n': goto hell;
      default: *n *= 10; *n += c - '0'; break; } }
hell:
  *n *= sign; }


int times[1'000'000];
int dp[1'000'001];
int main()
{
    ios_base::sync_with_stdio(false);

    int n, c, t;
    readn(&n);
    readn(&c);
    readn(&t);
    
    for (int i = 0; i < n; i++) {
        readn(times+i);
    }

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
