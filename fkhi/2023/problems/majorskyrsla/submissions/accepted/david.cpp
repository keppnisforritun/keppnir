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

void solve() {
    ll n,k;
    cin >> n >> k;
    vi ls,rs;
    rs.pb(n);
    FORD(i,n-1,1) {
        if(i <= k) {
            k-= i;
            ls.pb(i);
        } else {
            rs.pb(i);
        }
    }
    sort(ALL(ls));
    sort(ALL(rs));
    vi sol(n);

    int a = ls.size();
    int b = n-a;

    FORD(i,n,n-a+1) {
        sol[ls[n-i]-1] = i;
    }
    FORS(i,b) {
        sol[rs[i-1]-1] = i;
    } 

    FORE(x,sol) cout << x << " ";
    cout << endl;
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