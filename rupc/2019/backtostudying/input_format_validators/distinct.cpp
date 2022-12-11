#include <iostream>
#include <unordered_set>
#include <cassert>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_set<long long> seen;
    for (int i = 0; i < n; i++) {
        long long d, c;
        cin >> d >> c;
        assert(seen.find(d) == seen.end());
        seen.insert(d);
    }

    return 42;
}

