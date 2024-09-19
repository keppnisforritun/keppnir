#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

bool incr(vi &i, vi &m) {
    for(int j = i.size() - 1; j >= 0; --j) {
        i[j]++;
        if(i[j] >= m[j]) i[j] = 0;
        else return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int l; cin >> l;
    vector<vector<string>> opts(l);
    vi mx(l), cur(l, 0);
    for(int i = 0; i < l; ++i) {
        cin >> mx[i];
        opts[i].resize(mx[i]);
        for(int j = 0; j < mx[i]; ++j)
            cin >> opts[i][j];
        sort(opts[i].begin(), opts[i].end());
    }
    vector<string> outp;
    do {
        string line = "";
        for(int i = 0; i < l; ++i)
            line += opts[i][cur[i]],
            line.push_back(' ');
        outp.push_back(line);
    } while(incr(cur, mx));
    sort(outp.begin(), outp.end());
    for(string s : outp)
        cout << s << '\n';
}
