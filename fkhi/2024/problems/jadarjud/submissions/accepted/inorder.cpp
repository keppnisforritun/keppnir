#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

struct uguf {
    vi par; 
    vii ops;
    vvi des;
    
    uguf(int n) : par(n, -1), des(n), ops() { }
    
    void print_group(int x, bool internal = false) {
        if(!internal) x = find(x);
        int k = rand() % (des[x].size() + 1);
        for(int i = 0; i < k; ++i)
            print_group(des[x][i], true);
        cout << x + 1 << ' ';
        for(int i = k; i < des[x].size(); ++i)
            print_group(des[x][i], true);
        if(!internal) cout << '\n';
    }

    void undo() {
        if(ops.empty()) return;
        if(ops.back().first != -1) {
            par[ops.back().first] = ops.back().second;
            ops.pop_back();
            des[ops.back().first].pop_back();
            par[ops.back().first] = ops.back().second;
        }
        ops.pop_back();
    }

    int find(int x) {
        while(par[x] >= 0) x = par[x];
        return x;
    }

    void unite(int x, int y) {
        x = find(x); y = find(y);
        if(x == y) {
            ops.emplace_back(-1, -1);
            return;
        }
        if(par[x] > par[y]) swap(x, y);
        ops.emplace_back(x, par[x]);
        ops.emplace_back(y, par[y]);
        par[x] += par[y];
        par[y] = x;
        des[x].push_back(y);
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
