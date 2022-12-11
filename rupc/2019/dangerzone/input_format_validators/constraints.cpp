#include <vector>
#include <utility>
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<long long,long long> > arr;
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;

        for (int j = 0; j < i; j++) {
            long long xp = arr[j].first,
                      yp = arr[j].second;

            assert((x-xp)*(x-xp) + (y-yp)*(y-yp) >= 80*80);
        }

        arr.push_back(make_pair(x,y));
    }

    return 42;
}

