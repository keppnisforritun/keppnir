#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef __int128_t ml;

std::ostream& operator<<(std::ostream& dest, ml value) {
    std::ostream::sentry s(dest);
    if(s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char* d = std::end(buffer);
        do {
            --d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while(tmp != 0);
        if(value < 0) {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if(dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

int snoob(int x) {
  int y = x & -x, z = x + y;
  return z | ((x ^ z) >> 2) / y; }

bool landau(vi &v) {
    int n = v.size();
    sort(v.begin(), v.end());
    for(int x : v) {
        if(x < 0) return false;
        if(x >= n) return false;
    }
    int sm = 0;
    for(int i = 0; i < n - 1; ++i) {
        sm += v[i];
        if(sm < i * (i + 1) / 2) return false;
    }
    sm += v.back();
    return sm == n * (n - 1) / 2;
}

ml getdp(vi v) {
    int n = v.size();
    sort(v.begin(), v.end());
    if(v.empty()) return 1;
    if(v[0] < 0) return 0;
    if(v.back() >= n) return 0;
    if(v.back() == v.size() - 1) {
        vi cp = v; cp.pop_back();
        return getdp(cp);
    }
    if(v.size() - 1 - v.back() > v[0]) {
        vi cp = v;
        for(int i = 0; i < cp.size(); ++i)
            cp[i] = n - 1 - cp[i];
        return getdp(cp);
    }
    int skp = v.size() - 1 - v.back();
    ml ans = 0;
    for(int msk = (1 << skp) - 1; msk < (1 << (n - 1)); msk = snoob(msk)) {
        vi cp = v; cp.pop_back();
        for(int i = 0; i < n - 1; ++i)
            if(msk & (1 << i)) cp[i]--;
        ans += getdp(cp);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    vi score(n);
    for(int i = 0; i < n; ++i)
        cin >> score[i];
    if(n == 0) cout << "1\n";
    else if(!landau(score)) cout << "0\n";
    else cout << getdp(score) << '\n';
}