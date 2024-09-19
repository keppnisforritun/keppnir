#include <bits/stdc++.h>

using namespace std;
using int_t = int32_t;

struct height_t {
    int_t val;
    int_t id;
    bool operator<(const height_t other) const {
        return val == other.val ? id < other.id : val < other.val;
    }
    height_t merge(const height_t other) const {
        return val == other.val ? height_t{ val, -1 } : max(*this, other);
    }
};

void dfs(int_t u, const vector<vector<int_t>>& children, vector<height_t>& heights, vector<int_t>& best) {
    if (children[u].empty()) {
        return;
    }
    height_t max_height = {-1, 1};
    for (auto v : children[u]) {
        dfs(v, children, heights, best);
        max_height = max_height.merge(heights[v]);
    }
    heights[u] = max_height;
    if (max_height.id != -1) {
        best[max_height.id] = u;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    map<string, int_t> ids;
    vector<string> places;

    auto read_name = [&ids, &places]() -> int_t {
        string name;
        cin >> name;
        auto res{ ids.try_emplace(name, ids.size()) };
        if (res.second) {
            places.push_back(name);
        }
        return res.first->second;
    };

    int_t n;
    cin >> n;
    vector<vector<int_t>> children(n);
    vector<height_t> heights(n);
    vector<int_t> best(n);
    vector<int_t> output_order;
    for (int_t i = 0; i < n; i++) {
        int_t subregion = read_name(), region = read_name();
        int_t height;
        cin >> height;
        if (subregion != region) {
            children[region].push_back(subregion);
        }
        if (height != -1) {
            output_order.push_back(subregion);
        }
        heights[subregion] = {height, subregion};
        best[i] = i;
    }

    dfs(0, children, heights, best);

    for (auto subregion : output_order) {
        cout << places[best[subregion]] << '\n';
    }
    cout << flush;

    return 0;
}
