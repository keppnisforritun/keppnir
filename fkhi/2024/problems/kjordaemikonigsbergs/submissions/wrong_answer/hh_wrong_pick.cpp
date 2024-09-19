#include <algorithm>
#include <iostream>
#include <optional>
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
optional<vector<edge_t>> havel_hakimi(std::vector<vertex_t> sequence)
{
    sort(sequence.begin(), sequence.end());
    int_t n = static_cast<int_t>(sequence.size());
    union_find uf(n);
    vector<edge_t> edges;
    for (int i = n - 1; i >= 0; i--)
    {
        sort(sequence.begin(), sequence.begin() + i);
        int j = i - 1;
        while (j >= 0 && sequence[i].degree > 0)
        {
            if (sequence[j].degree == 0)
            {
                return nullopt;
            }
            edges.emplace_back(sequence[i].label, sequence[j].label);
            uf.unite(i, j);
            sequence[i].degree--;
            sequence[j].degree--;
            j--;
        }
        if (sequence[i].degree != 0)
        {
            return nullopt;
        }
    }
    return uf.components == 1 ? optional{ edges } : nullopt;
}

int main()
{
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
        cout << n << " " << m << endl;
        for (auto [u, v] : result.value())
        {
            cout << u + 1 << " " << v + 1 << endl;
        }
    }
    else
    {
        cout << "Omogulegt!" << endl;
    }
}
