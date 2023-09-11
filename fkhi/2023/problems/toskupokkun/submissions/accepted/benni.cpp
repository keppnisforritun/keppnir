#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    cin.sync_with_stdio(false);
    ll n, T;
    cin >> n >> T;
    ll lo = 0, hi = 1000000000;
    ll bst = -1;
    vector<ll> X(n), Y(n), Z(n);
    for(int i = 0; i < n; i++) cin >> X[i] >> Y[i] >> Z[i];

    while(lo <= hi) {
        ll mid = (lo+hi)/2;
        ll tm = 0;
        bool can = true;
        for(int i = 0; i < n; i++) {
            vector<ll> H = {X[i], Y[i], Z[i]};
            sort(H.begin(), H.end());
            ll mn_time = T+1;
            do {
                if(H[0] <= mid && H[1] <= mid) mn_time = min(mn_time, H[2]);
            } while(next_permutation(H.begin(), H.end()));
            if(mn_time == T+1) {
                can = false;
                break;
            } else tm += mn_time;
        }

        if(can && tm <= T) {
            bst = mid;
            hi = mid-1;
        } else lo = mid+1;

    }

    if(bst == -1) cout << "Omogulegt!" << endl;
    else cout << bst << endl;

}
