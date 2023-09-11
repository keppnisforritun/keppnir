#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.sync_with_stdio(false);

    int n,c,t;
    cin >> n >> c >> t;

    vector<int> A(n);
    for(int i = 0; i < n; i++) cin >> A[i];
    sort(A.begin(), A.end());


    vector<int> memo(n+1, 0);

    for(int i = n-1; i >= 0; i--) {
        // fill new coffee
        int lo = i+1, hi = n-1;
        int bst = -1;
        while(lo <= hi) {
            int mid = (lo+hi)/2;
            if(A[mid] >= A[i] + t) {
                bst = mid;
                hi = mid-1;
            } else {
                lo = mid+1;
            }
        }

        if(bst != -1) {
            for(int j = bst; j < min(bst + c, n); j++) {
                memo[i] = max(memo[i], memo[j] + (j - bst + 1));
            }
        }
    }

    cout << memo[0] << endl;

    /*
    vector<vector<int>> memo(n+10, vector<int>(c+1, -1));
    for(int i = 0; i <= c; i++) memo[n][i] = 0;

    vector<int> curr_memo(c+1, 0);
    for(int i = n-1; i >= 0; i--) {
        // fill new coffee
        int lo = i+1, hi = n-1;
        int bst = -1;
        while(lo <= hi) {
            int mid = (lo+hi)/2;
            if(A[mid] >= A[i] + t) {
                bst = mid;
                hi = mid-1;
            } else {
                lo = mid+1;
            }
        }

        for(int j = c; j >= 0; j--) {
            int add = j > 0 ? 1 : 0;
            if(bst != -1) memo[i][j] = max(memo[i][j], memo[bst][c] + add);
            memo[i][j] = max(memo[i][j], memo[i+1][j - add] + add);
        }

    }


    cout << memo[0] << endl;
    */
}


