#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;


int main() {
    int n;
    cin >> n;
    vector<ii> A(n);
    for(int i = 0; i < n; i++) cin >> A[i].first >> A[i].second;
    int curr = 0;
    for(int i = 1; i < n; i++) {
        int t1 = max(A[i].first  /  A[curr].second-1, 0);
        int t2 = max(A[curr].first / A[i].second-1, 0);

        A[i].first -= min(t1, t2) * A[curr].second;
        A[curr].first -= min(t1, t2) * A[i].second;

        while(true) {
            if(A[i].first <= 0) break;
            A[i].first -= A[curr].second;
            if(A[i].first <= 0) break;
            if(A[curr].first <= 0) break;
            A[curr].first -= A[i].second;
            if(A[curr].first <= 0) break;
        }

        if(A[i].first > A[curr].first) curr = i;
    }
    cout << curr+1 << endl;
}
