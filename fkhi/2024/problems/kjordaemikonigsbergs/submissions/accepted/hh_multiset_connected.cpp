#include <algorithm>
#include <iostream>
#include <optional>
#include <set>
#include <vector>

using namespace std;

using int_t = long long;

struct vertex_t
{
    int_t label;
    int_t degree;
};

bool operator<(const vertex_t a, vertex_t b)
{
    return a.degree == b.degree ? a.label < b.label : a.degree < b.degree;
}

struct union_find {
    int_t components;
    vector<int_t> p;
    union_find(int_t n) : components(n), p(n, -1) {
    }

    int_t find(int_t x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    bool unite(int_t x, int_t y) {
        int_t xp = find(x), yp = find(y);
        if (xp == yp) {
            return false;
        }
        if (p[xp] > p[yp]) {
            swap(xp, yp);
        }
        p[xp] += p[yp];
        p[yp] = xp;
        components--;
        return true;
    }
    size_t size(int_t x) {
        return -p[find(x)];
    }
};

using edge_t = pair<int_t, int_t>;

// Direct usage of Havel and Hakimi
optional<vector<edge_t>> havel_hakimi(const std::vector<vertex_t> &sequence)
{
    union_find uf(sequence.size());
    multiset<vertex_t> values(sequence.begin(), sequence.end());
    vector<edge_t> edges;
    while (!values.empty())
    {
        auto cur_it = values.begin();
        auto [i, amount] = *cur_it;
        values.erase(cur_it);
        vector<vertex_t> buffer;
        while (amount--)
        {
            if (values.empty())
            {
                return nullopt;
            }
            auto [j, other_amount] = *prev(values.end());
            if (other_amount == 0)
            {
                return nullopt;
            }
            edges.push_back({i, j});
            uf.unite(i, j);
            buffer.push_back({j, other_amount - 1});
            values.erase(prev(values.end()));
        }
        for (auto v : buffer)
        {
            if (v.degree > 0)
            {
                values.insert(v);
            }
        }
    }
    return uf.components <= 1 ? optional{ edges } : nullopt;
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
