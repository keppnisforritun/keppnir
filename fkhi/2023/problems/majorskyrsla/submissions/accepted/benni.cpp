#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, k;
    cin >> n >> k;
    vector<int> A(n, -1);
    int at = 1;
    for(int i = n-2; i >= 0; i--) {
        if(i+1 <= k) {
            k -= i+1;
            A[i] = at;
            at++;
        }
    }
    int p = 1;
    for(int i = 0; i < n; i++) {
        if(A[i] != -1) A[i] += (n - at+1);
        else {
            A[i] = p;
            p++;
        }
    }
    for(auto a : A) cout << a << " ";
    cout << endl;
}

