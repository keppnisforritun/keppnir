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

using edge_t = pair<int_t, int_t>;

// Direct usage of Havel and Hakimi
optional<vector<edge_t>> havel_hakimi(std::vector<vertex_t> sequence)
{
    sort(sequence.begin(), sequence.end());
    int_t n = static_cast<int_t>(sequence.size());
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
            sequence[i].degree--;
            sequence[j].degree--;
            j--;
        }
        if (sequence[i].degree != 0)
        {
            return nullopt;
        }
    }
    return edges;
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
