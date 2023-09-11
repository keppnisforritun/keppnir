#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 ml;

void ins(map<ll,int> &m, ll &x, ll d) {
    while(x % d == 0) {
        if(!m.count(d)) m[d] = 0;
        m[d] += 1;
        x /= d;
    }
}

map<ll,int> factor(ll x) {
    map<ll,int> fac;
    while(x % 2 == 0) x /= 2;
    ins(fac, x, 3);
    for(ll d = 5; d * d <= x; d += 6) {
        ins(fac, x, d);
        ins(fac, x, d + 2);
    }
    if(x != 1) ins(fac, x, x);
    return fac;
}

void divisors(map<ll,int> &fac, map<ll,int>::iterator it, ll d, ll phi, vector<pair<ll,ll>> &div) {
    if(it == fac.end()) {
        div.push_back(make_pair(d, phi));
        return;
    }
    auto itcp = it; itcp++;
    for(int i = 0; i <= it->second; ++i) {
        divisors(fac, itcp, d, phi, div);
        d *= it->first;
        if(i == 0) phi *= it->first - 1;
        else phi *= it->first;
    }
}

ml mod_pow(ml b, ml e, ml m) {
    ml res = 1;
    while(e) {
        if(e & 1) res = res * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll egcd(ll a, ll b, ll& x, ll& y) {
  if(b == 0) { x = 1; y = 0; return a; }
  ll d = egcd(b, a % b, x, y);
  x -= a / b * y; swap(x, y); return d; }

ll mod_inv(ll a, ll m) {
  ll x, y, d = egcd(a, m, x, y);
  return d == 1 ? (x%m+m)%m : -1; }

const ll mod = 1e9 + 7;
const ml mod2 = ((ml) mod) * mod;

int main() {
    ios_base::sync_with_stdio(false);
    ll n, t; cin >> t;
    while(t--) {
        cin >> n;
        auto fac = factor(n);
        vector<pair<ll,ll>> divs;
        divisors(fac, fac.begin(), 1, 1, divs);
        ml ans = 0;
        for(auto p : divs) {
            ll d = p.first, phi = p.second;
            ans += phi * mod_pow(2, n / d, mod2);
            ans %= mod;
        }
        if(n % mod == 0) {
            ans /= mod;
        } else {
            ans %= mod;
            ans *= mod_inv(n, mod);
            ans %= mod;
        }
        ans *= mod_inv(mod_pow(2, n, mod), mod);
        ans %= mod;
        cout << ((ll) ans) << '\n';
    }
}


