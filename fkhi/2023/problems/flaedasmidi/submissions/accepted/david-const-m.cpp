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

int jnt;
vii e;
int n,m=1024;

vi merge(int x, int y) {
    if(x == y) return {x + n};
    int m = (x+y)/2;
    vi l = merge(x,m);
    vi r = merge(m+1,y);

    int t = l.size();
    vi res;
    FOR(i,t) {
        jnt++;
        res.pb(jnt);
        e.pb({jnt,l[i]});
        e.pb({jnt,r[i]});
        jnt++;
        res.pb(jnt);
        e.pb({jnt,l[i]});
        e.pb({jnt,r[i]});
    }
    return res;
}

void solve() {
    int rm;
    cin >> n >> rm;
    jnt = n + m+1;

    vi ep = merge(1,m);
    FORS(i,n) {
        e.pb({i,ep[i-1]});
    }
    FORT(i,n+1,n+1+m-rm) {
        e.pb({rm+i,ep[i-1]});
    }
    cout << jnt << " " << e.size() << endl;
    FORE(x,e) {
        cout << x.F << " " << x.S << endl;
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