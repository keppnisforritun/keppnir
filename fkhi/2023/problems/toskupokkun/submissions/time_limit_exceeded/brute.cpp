#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n; long long t;
    cin >> n >> t;
    set<int> sz;
    vector<int> x(n), y(n), z(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> z[i];
        if(x[i] > y[i]) swap(x[i], y[i]);
        if(x[i] > z[i]) swap(x[i], z[i]);
        if(y[i] > z[i]) swap(y[i], z[i]);
        sz.insert(x[i]);
        sz.insert(y[i]);
        sz.insert(z[i]);
    }
    for(int l : sz) {
        long long curt = 0;
        bool valid = true;
        for(int i = 0; i < n; ++i) {
            if(y[i] > l) {
                valid = false;
                break;
            }
            if(z[i] <= l) curt += x[i];
            else curt += z[i];
        }
        if(!valid) continue;
        if(curt > t) continue;
        cout << l << '\n';
        return 0;
    }
    cout << "Omogulegt!\n";
}
