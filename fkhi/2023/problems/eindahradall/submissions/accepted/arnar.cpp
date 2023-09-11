#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) \
  it = (c).begin(); it != (c).end(); ++it)
#define fs first
#define sc second
#define pb push_back
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);

const double EPS = 1e-9;
const double pi = acos(-1);
typedef unsigned long long ull;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

template <class T>
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }

template <class T>
T mod_pow(T b, T e, T m) {
  T res = T(1);
  b = b % m;
  while (e) {
    if (e & T(1)) res = smod(res * b, m);
    b = smod(b * b, m), e >>= T(1); }
  return res; }

template <class T>
bool is_probable_prime(T n, int k) {
  if (~n & 1) return n == 2;
  if (n <= 3) return n == 3;
  int s = 0; T d = n - 1;
  while (~d & 1) d >>= 1, s++;
  while (k--) {
    T a = (n - 3) * rand() / RAND_MAX + 2;
    T x = mod_pow(a, d, n);
    if (x == 1 || x == n - 1) continue;
    bool ok = false;
    rep(i,0,s-1) {
      x = (x * x) % n;
      if (x == 1) return false;
      if (x == n - 1) { ok = true; break; }
    }
    if (!ok) return false;
  } return true; }

template <class T>
T rho(T n, T seed) {
    T i = 0, k = 2;
    T x = seed, y = seed;
    while (i < 1000000) {
        i++;
        x = (x*x + n - 1) % n;
        T d = gcd(abs(y - x), n);
        if (d != 1 && d != n) return d;
        if (i == k) {
            y = x;
            k = k*2;
        }
    }
    return 1;
}

template <class T>
vector<T> factor(T n) {
    if (n == 1) {
        return { };
    }
    if (is_probable_prime(n, 20)) {
        return { { n } };
    }
    vector<T> res;
    for (T i = 2; i*i*i <= n; i += (i&1) + 1)
    {
        while (n % i == 0) {
            res.push_back(i);
            n /= i;
        }
    }
    if (res.size() == 0) {
        for (T seed_value : {2,3,5,7,11,13,1031}) {
            T a_factor = rho(n, static_cast<T>(seed_value));
            if (a_factor != 1) {
                T other = n / a_factor;
                return { { min(a_factor, other), max(a_factor, other) } };
            }
        }
        assert(false);
    }

    if (n != 1) {
        for (auto x : factor(n)) {
            res.push_back(x);
        }
    }
    return res;
}

template <class T>
vector<pair<T, T>> divisors(T n) {
    map<T, T> cnt;
    vector<pair<T, T>> res{ { 1, 1 } };
    for (auto fac : factor(n))
    {
        if(fac != 2) cnt[fac]++;
    }

    for (auto p : cnt) {
        auto old_size = res.size();
        for (size_t j = 0; j < old_size; j++) {
            auto x = res[j].first;
            auto y = res[j].second;
            for (T i = 0; i < p.second; i++) {
                x *= p.first;
                if (i == 0) y *= p.first - 1;
                else y *= p.first;
                res.emplace_back(x, y);
            }
        }
    }
    return res;
}

void solve() {
    int64_t n_inp;

    cin >> n_inp;

    auto n{ static_cast<__int128>(n_inp) };

    __int128 res{ 0 }, M{ 1'000'000'007 }, MM { M * M };
    __int128 two{ 2 };

    for (auto [d, phid] : divisors(n)) {
        __int128 nd = n/d;
        __int128 twond = mod_pow(two, nd, MM);
        res = (res + twond * phid) % MM;
    }

    if (n % M == 0) {
        res /= M;
    }
    else {
        res %= MM;
        res = res * mod_pow(n, M * (M - 1) - 1, MM) % MM;
    }
    res = res * mod_pow(two, M * (M - 1) - n, MM) % MM;
    cout << static_cast<ll>(res % M) << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) solve();


    return 0;
}

