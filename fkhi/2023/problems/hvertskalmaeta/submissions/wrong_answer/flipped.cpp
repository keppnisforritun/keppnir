#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

int main()
{
    ios_base::sync_with_stdio(false);
    
    string municipality;

    if (!(municipality == "Akureyrarbaer" || municipality == "Fjardabyggd" || municipality == "Mulathing")) {
        cout << "Akureyri" << endl;
    }
    else {
        cout << "Reykjavik" << endl;
    }

    return 0;
}
