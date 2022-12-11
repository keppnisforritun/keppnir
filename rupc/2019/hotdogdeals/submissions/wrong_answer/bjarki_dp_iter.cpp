#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 1000000000;

int mem[5010][5010];

int main() {
    int pylsur, gos;
    cin >> pylsur >> gos;

    for (int a = 0; a <= pylsur; a++) {
        for (int b = 0; b <= gos; b++) {
            if (a == 0 && b == 0) {
                mem[a][b] = 0;
            } else {

                int cost = INF;
                if (a >= 2 && b >= 1) cost = min(cost, 549 + mem[a-2][b-1]);
                if (a >= 1 && b >= 1) cost = min(cost, 499 + mem[a-1][b-1]);
                if (a >= 0 && b >= 1) cost = min(cost, 249 + mem[a-0][b-1]);
                if (a >= 1 && b >= 0) cost = min(cost, 299 + mem[a-1][b-0]);
                mem[a][b] = cost;
            }
        }
    }

    cout << mem[pylsur][gos] << endl;

    return 0;
}

