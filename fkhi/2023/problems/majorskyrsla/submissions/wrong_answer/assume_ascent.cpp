#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    ll n, k; cin >> n >> k;
    if(n == 1) {
        cout << "1\n";
        return 0;
    }
    deque<int> h1, h2; 
    h1.push_back(1);
    h2.push_front(2);
    for(int i = 3; i <= n; ++i) {
        if(k == 0) {
            while(h2.size() > 0) {
                h1.push_back(h2.front());
                h2.pop_front();
            }
            h2.push_back(i);
        } else if(k >= i - 1) {
            h2.push_front(i);
            k -= i - 1;
        } else {
            int desc = 0;
            if(h2.size() > 0 && h1.back() > h2.front()) desc++;
            for(int j = 0; j < h1.size() - 1; ++j)
                if(h1[j] > h1[j + 1]) desc++;
            for(int j = 0; j < h2.size() - 1; ++j)
                if(h2[j] > h2[j + 1]) desc++;
            if(k == desc + 1) {
                h1.push_front(i);
                k = 0;
            } else if(k < desc + 1) {
                for(int j = h2.size() - 1; j >= 1; --j) {
                    if(h2[j - 1] > h2[j]) k--;
                    if(k == 0) {
                        h2.insert(h2.begin() + j, i);
                        break;
                    }
                }
                if(k > 0) {
                    for(int j = h1.size() - 1; j >= 1; --j) {
                        if(h1[j - 1] > h1[j]) k--;
                        if(k == 0) {
                            h1.insert(h1.begin() + j, i);
                            break;
                        }
                    }
                }
            } else {
                int skp = i - 1 - k - 1;
                for(int j = h1.size() - 1; j >= 1; --j) {
                    if(h1[j - 1] < h1[j]) skp--;
                    if(skp == 0) {
                        h1.insert(h1.begin() + j, i);
                        break;
                    }
                }
                k = 0;
            }
        }
    }
    for(int x : h1) cout << x << ' ';
    for(int x : h2) cout << x << ' ';
    cout << '\n';
}
