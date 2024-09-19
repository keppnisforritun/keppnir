#include <algorithm>
#include <iostream>
#include <optional>
#include <set>
#include <stack>
#include <vector>

using namespace std;

using int_t = long long;

struct vertex_t
{
    int_t label;
    int_t degree;
};

using edge_t = pair<int_t, int_t>;

struct bounded_decrementing_queue {
    int_t n, min_key, max_key;
    // Stores the labels of 
    vector<vector<int_t>> data;
    // Functionally a singly linked list
    vector<int_t> next_key;

    // O(n)
    bounded_decrementing_queue(const vector<vertex_t>& v) : n(v.size()) {
        min_key = n - 1;
        max_key = 0;
        data.resize(n);
        next_key.resize(n);
        for (const auto [label, degree] : v) {
            data[degree].push_back(label);
            min_key = min(min_key, degree);
            max_key = max(max_key, degree);
        }

        // Compute initial linked list
        int_t previous = -1;
        for (int_t i = 0; i < n; i++) {
            if (!data[i].empty()) {
                next_key[i] = previous;
                previous = i;
            }
        }
    }

    // O(1)
    bool empty() const {
        return min_key > max_key || min_key + max_key == 0;
    }

    // Recursively compressed paths and removes empty linked list nodes
    // Amortized O(alpha(n)) which is essentially constant in practice
    int_t get_next(int_t key) {
        if (key < min_key) {
            return -1;
        }
        if (key > max_key) {
            return max_key;
        }
        auto nxt = next_key[key];
        if (nxt >= 0 && data[nxt].empty()) {
            nxt = next_key[key] = get_next(nxt);
        }
        return nxt;
    }

    // O(1)
    vertex_t front() {
        return {data[min_key].back(), min_key};
    }

    // Amortized O(n)
    void pop_front() {
        data[min_key].pop_back();
        while (min_key < n && data[min_key].empty()) {
            min_key++;
        }
    }

    // Amortized O(alpha(n))
    optional<vector<int_t>> decrement_back(int_t count) {
        stack<int_t> keys;
        int_t total_count = 0;
        int_t cur_key = max_key;
        while (total_count < count && cur_key > 0) {
            total_count += data[cur_key].size();
            keys.push(cur_key);
            cur_key = get_next(cur_key);
        }
        if (total_count < count) {
            return {};
        }

        int_t skip_count = total_count - count;
        vector<int_t> res;
        res.reserve(count);
        while (!keys.empty()) {
            cur_key = keys.top();
            keys.pop();
            for (int_t i = ssize(data[cur_key]) - 1; i >= skip_count; i--) {
                res.push_back(data[cur_key].back());
                if (data[cur_key - 1].empty()) {
                    next_key[cur_key - 1] = get_next(cur_key);
                    next_key[cur_key] = cur_key - 1;
                }
                data[cur_key - 1].push_back(data[cur_key].back());
                data[cur_key].pop_back();
                min_key = min(min_key, cur_key - 1);
            }
            if (cur_key == max_key && skip_count == 0) {
                max_key = get_next(max_key);
            }
            skip_count = 0;
        }
        return res;
    }
};

// Direct usage of Havel and Hakimi
optional<vector<edge_t>> havel_hakimi(const std::vector<vertex_t> &sequence)
{
    int_t n = ssize(sequence);
    int_t sm = 0;
    if (n == 1 && sequence[0].degree == 0) {
        return vector<edge_t>{};
    }
    for (auto [label, degree] : sequence) {
        // Degree out of bounds
        if (degree <= 0 || degree >= n) {
            return {};
        }
        sm += degree;
    }
    // Odd number of stubs
    if (sm % 2 != 0) {
        return {};
    }
    // Not enough edges to make connected
    if (sm < 2 * (n - 1)) {
        return {};
    }

    bounded_decrementing_queue values(sequence);
    vector<edge_t> edges;
    while (!values.empty())
    {
        const auto [i, amount] = values.front();
        values.pop_front();
        if (amount == 0) {
            continue;
        }
        const auto neighbors{ values.decrement_back(amount) };
        if (!neighbors.has_value()) {
            return {};
        }
        for (auto j : neighbors.value()) {
            edges.push_back({i, j});
        }
    }
    return edges;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int_t n;
    cin >> n;
    vector<vertex_t> sequence(n);
    int_t m = 0;
    for (int_t i = 0; i < n; i++)
    {
        sequence[i].label = i;
        cin >> sequence[i].degree;
        m += sequence[i].degree;
    }
    m /= 2;

    const auto result{havel_hakimi(sequence)};

    if (result.has_value())
    {
        cout << n << " " << m << '\n';
        for (auto [u, v] : result.value())
        {
            cout << u + 1 << " " << v + 1 << '\n';
        }
    }
    else
    {
        cout << "Omogulegt!" << endl;
    }
}
