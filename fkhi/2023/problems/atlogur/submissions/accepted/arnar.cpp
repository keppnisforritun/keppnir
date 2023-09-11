#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) \
  it = (c).begin(); it != (c).end(); ++it)
#define fs first
#define sc second
#define pb push_back
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);

const double EPS = 1e-9;
const double pi = acos(-1);
typedef unsigned long long ull;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> health(n);
    vector<int> damage(n);
    for (int i = 0; i < n; i++) {
        cin >> health[i] >> damage[i];
    }

    int last = 0;
    for (int i = 1; i < n; i++) {
        int current = last, other = i;
        while (health[current] > 0) {
            health[other] -= damage[current];
            swap(current, other);
        }
        last = other;
    }

    cout << last + 1 << endl;

    return 0;
}
