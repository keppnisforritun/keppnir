#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

struct uguf {
    vi fst, lst, nxt; vii ops;
    
    uguf(int n) : fst(n), lst(n), nxt(n, -1), ops() { 
        iota(fst.begin(), fst.end(), 0);
        iota(lst.begin(), lst.end(), 0);
    }
    
    void print_group(int x) {
        x = find(x);
        cout << x + 1 << ' ';
        while(nxt[x] >= 0) {
            x = nxt[x];
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }

    void undo() {
        if(ops.empty()) return;
        if(ops.back().first != -1) {
            nxt[ops.back().first] = ops.back().second;
            ops.pop_back();
            nxt[ops.back().first] = ops.back().second;
            ops.pop_back();
            fst[ops.back().first] = ops.back().second;
            ops.pop_back();
            lst[ops.back().first] = ops.back().second;
        }
        ops.pop_back();
    }

    int find(int x) {
        while(fst[x] != x) x = fst[x];
        return x;
    }

    void unite(int x, int y) {
        x = find(x); y = find(y);
        if(x == y) {
            ops.emplace_back(-1, -1);
            return;
        }
        if(nxt[lst[x]] > nxt[lst[y]]) swap(x, y);
        ops.emplace_back(x, lst[x]);
        ops.emplace_back(y, fst[y]);
        ops.emplace_back(lst[x], nxt[lst[x]]);
        ops.emplace_back(lst[y], nxt[lst[y]]);
        nxt[lst[y]] += nxt[lst[x]];
        nxt[lst[x]] = fst[y];
        fst[y] = x;
        lst[x] = lst[y];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, q, a, b; cin >> n >> q;
    uguf uf(n);
    while(q--) {
        char op; cin >> ws >> op;
        if(op == 'j') {
            cin >> a >> b;
            a--; b--;
            uf.unite(a, b);
        } else if(op == 'u') {
            uf.undo();
        } else {
            cin >> a; a--;
            uf.print_group(a);
        }
    }
}
