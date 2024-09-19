#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int L, E; cin >> L >> E;
    vector<string> ename(E), lname(L);
    vector<ll> estr(E), ecnt(E), lstr(L), lcnt(L);
    vvi immun(L, vi(E, 0));
    map<string,int> eind;
    for(int i = 0; i < E; ++i) {
        cin >> ename[i] >> estr[i] >> ecnt[i];
        eind[ename[i]] = i;
    }
    for(int i = 0; i < L; ++i) {
        cin >> lname[i] >> lstr[i] >> lcnt[i];
        int k; cin >> k;
        for(int j = 0; j < k; ++j) {
            string nam; cin >> nam;
            immun[i][eind[nam]] = 1;
        }
    }
    ll lo = 0, hi = 1'000'000'000'000LL;
    while(hi > lo) {
        ll md = hi - (hi - lo) / 2;
        set<pair<ll,ll>> unassigned;
        auto curcnt = ecnt;
        for(int i = 0; i < E; ++i)
            unassigned.insert(make_pair(estr[i], i));
        bool ok = true;
        for(int i = 0; i < L; ++i) {
            auto it = unassigned.lower_bound(make_pair(lstr[i], 0));
            __int128_t left = md; left *= lcnt[i];
            while(left > 0) {
                if(it == unassigned.end()) {
                    ok = false;
                    break;
                }
                if(immun[i][it->second]) {
                    it++;
                    continue;
                }
                ll take = min(left, (__int128_t) curcnt[it->second]);
                left -= take;
                curcnt[it->second] -= take;
                bool rem = curcnt[it->second] == 0;
                auto cp = it; it++;
                if(rem) unassigned.erase(cp); 
            }
        }
        if(ok) lo = md;
        else hi = md - 1;
    }
    cout << lo << '\n';
}

