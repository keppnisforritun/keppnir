#include <bits/stdc++.h>
#include <immintrin.h>

typedef int v4si __attribute__ ((vector_size (16)));
typedef short v8hi __attribute__ ((vector_size (16)));
typedef char v16qi __attribute__ ((vector_size (16)));

using namespace std;
typedef long long ll;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

static int
linear_sentinel_sse2_nobranch (const int *arr, int start, int n, int key)  {
        v4si *in_data = (v4si*)arr;
        v4si key4 = { key, key, key, key };
        int i = start/4, res = n;
        for (;;) {
                v4si cmp0 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 0]);
                v4si cmp1 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 1]);
                v4si cmp2 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 2]);
                v4si cmp3 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 3]);
                v8hi pack01 = __builtin_ia32_packssdw128 (cmp0, cmp1);
                v8hi pack23 = __builtin_ia32_packssdw128 (cmp2, cmp3);
                v16qi pack0123 = __builtin_ia32_packsswb128 (pack01, pack23);
                res = __builtin_ia32_pmovmskb128 (pack0123);
                if (res != 0xffff)
                        return max(start, i * 4 + __builtin_ctz (~res));
                cmp0 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 4]);
                cmp1 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 5]);
                cmp2 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 6]);
                cmp3 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 7]);
                pack01 = __builtin_ia32_packssdw128 (cmp0, cmp1);
                pack23 = __builtin_ia32_packssdw128 (cmp2, cmp3);
                pack0123 = __builtin_ia32_packsswb128 (pack01, pack23);
                res = __builtin_ia32_pmovmskb128 (pack0123);
                if (res != 0xffff)
                        return max(start, (i+4) * 4 + __builtin_ctz (~res));
                cmp0 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 8]);
                cmp1 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 9]);
                cmp2 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 10]);
                cmp3 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 11]);
                pack01 = __builtin_ia32_packssdw128 (cmp0, cmp1);
                pack23 = __builtin_ia32_packssdw128 (cmp2, cmp3);
                pack0123 = __builtin_ia32_packsswb128 (pack01, pack23);
                res = __builtin_ia32_pmovmskb128 (pack0123);
                if (res != 0xffff)
                        return max(start, (i+8) * 4 + __builtin_ctz (~res));
                cmp0 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 12]);
                cmp1 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 13]);
                cmp2 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 14]);
                cmp3 = __builtin_ia32_pcmpgtd128 (key4, in_data [i + 15]);
                pack01 = __builtin_ia32_packssdw128 (cmp0, cmp1);
                pack23 = __builtin_ia32_packssdw128 (cmp2, cmp3);
                pack0123 = __builtin_ia32_packsswb128 (pack01, pack23);
                res = __builtin_ia32_pmovmskb128 (pack0123);
                if (res != 0xffff)
                        return max(start, (i+12) * 4 + __builtin_ctz (~res));
                i += 16;
        }
}

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

int times[1'048'576];
int dp[1'048'576];
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
    times[n] = 2'000'000'000;
    times[n+1] = 2'000'000'000;
    times[n+2] = 2'000'000'000;
    times[n+3] = 2'000'000'000;

    int res = 0;
    for (int i = n-1; i >= 0; i--) {
        int start = max(i+1, linear_sentinel_sse2_nobranch(times, i+1, n, times[i]+t));
        int end = min(start+c, n);
        for (int j = start; j < end; j++) {
            dp[i] = max(dp[i], j - start + dp[j] + 1);
        }
        res = max(res, dp[i]);
    }

    cout << res << endl;

    return 0;
}
