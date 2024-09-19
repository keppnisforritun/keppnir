#include<bits/stdc++.h>
using namespace std;

struct kahan {
    double sm, c;
    kahan() : sm(0.0), c(0.0) { }
    void add_val(double d) {
        double y = d - c;
        double t = sm + y;
        c = (t - sm) - y;
        sm = t;
    }
    double get_sm() {
        return sm;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout << setprecision(15);
    int n; cin >> n;
    if(n == 1) {
        double x; cin >> x; 
        cout << x << '\n';
        return 0;
    }
    vector<double> inp(n);
    kahan sm, lgsm;
    for(int i = 0; i < n ; ++i) {
        cin >> inp[i];
        sm.add_val(inp[i]);
        lgsm.add_val(log(inp[i]));
    }
    sort(inp.begin(), inp.end());
    vector<double> cur = { sm.get_sm() / n, exp(lgsm.get_sm() / n), inp[inp.size() / 2] };
    sort(cur.begin(), cur.end());
    while(cur.back() - cur[0] > 1e-9) {
        double med = cur[1];
        double avg = (cur[0] + cur[1] + cur[2]) / 3.0;
        double geo = cbrt(cur[0] * cur[1] * cur[2]);
        cur = { med, avg, geo };
        sort(cur.begin(), cur.end());
    }
    cout << cur[1] << '\n';
}
