#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int major(vi &pi) {
    int sm = 0, n = pi.size();
    for(int i = 0; i < n - 1; ++i)
        if(pi[i] > pi[i + 1])
            sm += i + 1;
    return sm;
}

int main() {
    srand(time(NULL));
    int n, k; cin >> n >> k;
    vi res;
    for(int i = 1; i <= n; ++i)
        res.push_back(i);
    while(major(res) != k) {
        random_shuffle(res.begin(), res.end());
    }
    for(int x : res) cout << x << ' ';
    cout << '\n';
}
