#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll read_time() {
    ll x; cin >> x;
    string s; cin >> s;
    if(s.rfind("min", 0) == 0) x *= 60;
    if(s.rfind("klu", 0) == 0) x *= 60 * 60;
    if(s.rfind("dag", 0) == 0) x *= 60 * 60 * 8;
    if(s.rfind("vik", 0) == 0) x *= 60 * 60 * 8 * 5;
    if(s == "ar") x *= 60 * 60 * 8 * 5 * 52;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    volatile long long t1, t2; 
    ll x; cin >> x; t1 = x;
    string s; cin >> s >> s;
    t1 *= 5;
    if(s != "arlega") t1 *= 52;
    if(s == "daglega") t1 *= 5;
    t1 *= read_time();
    t2 = read_time();
    while(t1 > 0) {
        t1--; t2--;
    }
    if(t2 > 0) cout << "Borgar sig ekki!\n";
    else cout << t1 - t2 << '\n';
}
