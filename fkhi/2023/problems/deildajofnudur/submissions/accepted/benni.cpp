#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            map<char,int> H;
            for(int z = i; z <= j; z++) H[s[z]]++;
            set<int> K;
            for(auto a : H) K.insert(a.second);
            if(K.size() == 1) ans = max(ans, j - i + 1);
        }
    }
    cout << ans << endl;
}
