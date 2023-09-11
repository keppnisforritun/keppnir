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
    string s;
    cin >> s;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        unordered_map<char, int> character_count;
        for (int j = i; j < n; j++) {
            character_count[s[j]]++;
            if (all_of(character_count.begin(),
                    character_count.end(),
                    [character_count](auto p) {
                        return p.second == character_count.begin()->second;
                })) {
                mx = max(mx, j - i + 1);
            }
        }
    }

    cout << mx << endl;

    return 0;
}
