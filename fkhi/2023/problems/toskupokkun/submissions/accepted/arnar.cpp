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

struct bag {
    int x, y, z;

    bool operator<(const bag& other) const {
        return z < other.z;
    }
};

bag bags[500000];

void readn(register long long *n) {
  long long sign = 1;
  register char c;
  *n = 0;
  while((c = getc_unlocked(stdin)) != '\n') {
    switch(c) {
      case '-': sign = -1; break;
      case ' ': goto hell;
      case '\n': goto hell;
      default: *n *= 10; *n += c - '0'; break; } }
hell:
  *n *= sign; }

void readn(register int *n) {
  int sign = 1;
  register char c;
  *n = 0;
  while((c = getc_unlocked(stdin)) != '\n') {
    switch(c) {
      case '-': sign = -1; break;
      case ' ': goto hell;
      case '\n': goto hell;
      default: *n *= 10; *n += c - '0'; break; } }
hell:
  *n *= sign; }

int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    long long t;
    readn(&n);
    readn(&t);


    for (int i = 0; i < n; i++) {
        readn(&bags[i].x);
        readn(&bags[i].y);
        readn(&bags[i].z);
        sort(&bags[i].x, &bags[i].x + 3);
    }

    sort(bags, bags+n);

    long long total_time = 0;
    int gate_size = 0;
    for (const auto bag : bags) {
        total_time += bag.z;
        gate_size = max(gate_size, bag.y);
    }
    
    for (const auto bag : bags) {
        if (bag.z <= gate_size) {
            total_time += bag.x - bag.z;
        }
        else if(total_time <= t) {
            cout << gate_size << endl;
            return 0;
        }
        else {
            gate_size = bag.z;
            total_time += bag.x - bag.z;
        }
    }
    if(total_time <= t) {
        cout << gate_size << endl;
        return 0;
    }
    cout << "Omogulegt!" << endl;

    return 0;
}
