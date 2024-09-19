#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s;
    while(cin >> s) {
        if(s.find("69") != string::npos ||
            s.find("420") != string::npos) {
            cout << "Mergjad!\n";
            return 0;
        }
    }
    cout << "Leim!\n";
    return 0;
}
