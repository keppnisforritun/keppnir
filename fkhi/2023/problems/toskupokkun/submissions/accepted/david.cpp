#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<double>
#define ld long double;
#define ii pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vc vector<char>
#define vs vector<string>
#define vd vector<double>
#define vcom vector<com>
#define vld vector<ld>
#define vll vector<ll>
#define vvi vector<vi>
#define vvii vector<vii>
#define vvc vector<vc>
#define vvs vector<vs>
#define vvll vector<vll>
#define vvd vector<vd>
#define vvcom vector<vcom>
#define vvld vector<vld>
#define FOR(x,n) for(int x=0;x<(n);x++)
#define FORS(x,n) for(int x=1;x<=(n);x++)
#define FORE(x,a) for(auto &x: a)
#define FORT(x,a,b) for(int x=(a);x<(b);x++)
#define FORD(x,a,b) for(int x=(a);x>=(b);x--)
#define ALL(x) x.begin(),x.end()
#define REP(n) for(int _ = 0; _ < n; _++)
#define MT make_tuple
#define MP make_pair
#define pb push_back
#define endl '\n'
#define F first
#define S second
#define vvvll vector<vvll>
#define sz(x) ((int)x.size())

vector<tuple<int,int,int>> b;
int n;
ll attempt(int s) {
    ll sm = 0;
    FOR(i,n) {
        int x,y,z;
        tie(x,y,z) = b[i];
        if(y > s) return 2e18;
        if(z > s) sm += z;
        else sm += x;
    }
    return sm;
}


void solve() {
    ll t;
    cin >> n >> t;
    FOR(i,n) {
        vi r(3);
        FOR(i,3) cin >> r[i];
        sort(ALL(r));

        b.pb({r[0],r[1],r[2]});
    }

    ll l = 0, r = 1e9 + 5;
    while(l < r) {
        ll m = (l + r) / 2;
        ll res = attempt(m);
        if(res <= t) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    if(l > 1e9+1) {
        cout << "Omogulegt!" << endl;
    } else {
        cout << l << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;

    while(t--) {
        solve();
    }
}