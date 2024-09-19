#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

void quit() {
    cout << "Omogulegt!\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    vi degs(n);
    for(int i = 0; i < n; ++i)
        cin >> degs[i];
    if(n == 1) {
        if(degs[0] == 0) {
            cout << "1 0\n";
            return 0;
        }
        quit();
    }
    int sm = 0;
    for(int i = 0; i < n; ++i) {
        if(degs[i] <= 0 || degs[i] >= n) quit();
        sm += degs[i];
    }
    if(sm % 2 != 0 || sm < 2 * (n - 1)) quit();
    vvi count(n);
    for(int i = 0; i < n; ++i)
        count[degs[i]].push_back(i);
    vi nxt(n); vii edges; 
    iota(nxt.begin(), nxt.end(), -1);
    int lo = 0, hi = n - 1;
    while(lo <= hi) {
        while(lo < n && count[lo].empty()) lo++;
        if(lo == n) break;
        int cur = count[lo].back();
        count[lo].pop_back();
        int left = lo, old_hi = hi;
        vii mov; vi cut;
        while(left > 0) {
            while(hi > 0 && count[hi].empty()) {
                if(count[nxt[hi]].empty())
                    cut.push_back(hi);
                hi = nxt[hi];
            }
            if(hi == 0) quit();
            int neigh = count[hi].back();
            count[hi].pop_back();
            edges.emplace_back(cur, neigh);
            if(hi != 1) mov.emplace_back(hi - 1, neigh);
            left--;
        }
        for(auto p : mov) {
            int ind = p.first, vert = p.second;
            count[ind].push_back(vert);
            if(nxt[ind + 1] != ind) {
                nxt[ind] = nxt[ind + 1];
                nxt[ind + 1] = ind;
            }
            hi = max(hi, ind);
            lo = min(lo, ind);
        }
        for(int ind : cut) {
            if(count[nxt[ind]].empty()) {
                if(hi == nxt[ind])
                    hi = nxt[nxt[ind]];
                nxt[ind] = nxt[nxt[ind]];
            }
        }
    }
    if(sm / 2 != edges.size()) quit();
    cout << n << ' ' << sm / 2 << '\n';
    for(auto e : edges) 
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
}
