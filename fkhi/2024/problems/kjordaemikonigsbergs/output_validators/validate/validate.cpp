#include "validate.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string.h>
#include <vector>
using namespace std;

using int_t = int64_t;

struct vertex_t {
    int_t label;
    int_t out_degree;
    int_t in_degree;
};

bool operator<(const vertex_t &a, vertex_t &b) {
    return a.out_degree == b.out_degree ? (a.in_degree == b.in_degree ? a.label < b.label : a.in_degree < b.in_degree)
                                        : a.out_degree < b.out_degree;
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

struct range_query_t {
    vector<int_t> data;
    range_query_t(const vector<int_t>& arr) : data(arr.size()+1) {
        for (size_t i = 0; i < arr.size(); i++) {
            data[i+1] = data[i] + arr[i];
        }
    }

    int_t operator()(const size_t left, const size_t right) const {
        return left <= right ? data[right+1] - data[left] : 0;
    }
};

enum class connectivity_t {
    no_restriction,
    weakly_connected,
    strongly_connected
};

bool directed{ false };
bool allow_multiedges{ false };
bool allow_self_loops{ false };
connectivity_t connectivity;
namespace {
    bool is_graphical_directed_multi(const vector<vertex_t> &seq) {
        assert(connectivity == connectivity_t::no_restriction);
        const int_t out_sum{ accumulate(seq.begin(), seq.end(), 0LL, [](const int_t x, const vertex_t v) { return x + v.out_degree; }) };
        const int_t in_sum{ accumulate(seq.begin(), seq.end(), 0LL, [](const int_t x, const vertex_t v) { return x + v.in_degree; }) };

        if (in_sum != out_sum) {
            return false;
        }

        if (allow_self_loops) {
            return true;
        }
        const int_t d_max{ accumulate(seq.begin(), seq.end(), 0LL,
                                      [](const int_t x, const vertex_t v) { return max(x, v.in_degree + v.out_degree); }) };

        return out_sum + in_sum >= 2 * d_max;
    }

    bool is_graphical_directed_simple_loopy(const vector<vertex_t> &seq) {
        assert(connectivity == connectivity_t::no_restriction);
        int_t n{ static_cast<int_t>(seq.size()) };
        vector<int_t> lower(n);
        vector<int_t> upper(n);
        for (int_t i = 0; i < n; i++) {
            lower[i] = seq[i].out_degree;
            upper[i] = seq[i].in_degree;
        }
        sort(lower.rbegin(), lower.rend());
        sort(upper.rbegin(), upper.rend());
        int_t lhs = 0, rhs = 0, rhs_index = 0;
        for (int_t k = 1; k <= n; k++) {
            lhs += lower[k - 1];
            while (rhs_index < n && upper[rhs] < k) {
                rhs += upper[rhs_index];
                rhs_index++;
            }

            if (lhs > rhs + (n - rhs_index) * k) {
                return false;
            }
        }
        return true;
    }


    bool is_graphical_strong_directed(const vector<vertex_t>& seq) {
        int_t n = static_cast<int_t>(seq.size());
        int_t total_out_degree = 0;
        int_t total_in_degree = 0;

        if (seq.size() == 0) {
            return false;
        }

        if (seq.size() == 1 && seq[0].in_degree == 0 && seq[0].out_degree == 0) {
            return true;
        }

        vector<vector<int_t>> buckets(n);
        for (auto [_, a, b] : seq) {
            total_out_degree += a;
            total_in_degree += b;
            if (a <= 0 || b <= 0 || a >= n || b >= n) {
                return false;
            }
            buckets[a].push_back(b);
        }

        if (total_in_degree != total_out_degree) {
            return false;
        }

        vector<pair<int_t, int_t>> sequence(n);
        {
            int_t ind = 0;
            for (int_t a = n-1; a >= 0; a--) {
                for (const auto b : buckets[a]) {
                    sequence[ind++] = {a, b};
                }
            }
        }

        int_t lhs{ 0 };
        int_t rhs_sum{ 0 };

        vector<int_t> over(n);

        int_t at = 0;
        int_t count = 0;
        for (const auto& [a, b] : sequence) {
            over[b]++;
            count++;
        }


        for (int_t k = 1; k < n; k++) {
            const auto [a, b] = sequence[k - 1];
            lhs += (b - a);

            while (at < k) {
                while (over[at] > 0) {
                    over[at]--;
                    count--;
                    rhs_sum += at;
                }
                at++;
            }
            if (b >= k) {
                over[b]--;
                count--;
            }
            else {
                rhs_sum -= b;
            }


            const auto rhs{ rhs_sum + k * count };
            if (lhs + rhs < 1) {
                return false;
            }
        }
        return true;
    }

    bool is_graphical_directed_simple_loopless(const vector<vertex_t> &seq) {
        int_t n = static_cast<int_t>(seq.size());
        int_t total_out_degree = 0;
        int_t total_in_degree = 0;

        if (connectivity == connectivity_t::weakly_connected && n == 0) {
            return false;
        }

        vector<vector<int_t>> buckets(n);
        for (auto [_, a, b] : seq) {
            total_out_degree += a;
            total_in_degree += b;
            if (a >= n || b >= n) {
                return false;
            }
            if (connectivity == connectivity_t::weakly_connected && a + b == 0LL && n > 1) {
                return false;
            }
            buckets[a].push_back(b);
        }

        if (total_in_degree != total_out_degree) {
            return false;
        }

        if (connectivity == connectivity_t::weakly_connected && (total_out_degree < n - 1)) {
            return false;
        }

        vector<pair<int_t, int_t>> sequence(n);
        {
            int_t ind = 0;
            for (int_t a = n - 1; a >= 0; a--) {
                for (const auto b : buckets[a]) {
                    sequence[ind++] = { a, b };
                }
            }
        }

        int_t lhs{ 0 };
        int_t lower_rhs_sum{ 0 };
        int_t upper_rhs_sum{ 0 };

        vector<int_t> lower_over(n);
        vector<int_t> upper_over(n);

        int_t lower_at = 0;
        int_t lower_count = 0;
        int_t upper_at = 0;
        int_t upper_count = 0;
        for (const auto &[a, b] : sequence) {
            upper_over[b]++;
            upper_count++;
        }

        for (int_t k = 1; k <= n; k++) {
            const auto [a, b] = sequence[k - 1];
            lhs += a;

            if (b >= k - 1) {
                lower_over[b]++;
                lower_count++;
            }
            else {
                lower_rhs_sum += b;
            }
            while (lower_at < k - 1) {
                while (lower_over[lower_at] > 0) {
                    lower_over[lower_at]--;
                    lower_count--;
                    lower_rhs_sum += lower_at;
                }
                lower_at++;
            }

            while (upper_at < k) {
                while (upper_over[upper_at] > 0) {
                    upper_over[upper_at]--;
                    upper_count--;
                    upper_rhs_sum += upper_at;
                }
                upper_at++;
            }
            if (b >= k) {
                upper_over[b]--;
                upper_count--;
            }
            else {
                upper_rhs_sum -= b;
            }

            const auto rhs{ lower_rhs_sum + (k - 1) * lower_count + upper_rhs_sum + k * upper_count };
            if (lhs > rhs) {
                return false;
            }
        }
        return connectivity == connectivity_t::strongly_connected ? is_graphical_strong_directed(seq) : true;
    }

    bool is_graphical_directed_simple(const vector<vertex_t> &seq) {
        return allow_self_loops ? is_graphical_directed_simple_loopy(seq) : is_graphical_directed_simple_loopless(seq);
    }

    bool is_graphical_directed(const vector<vertex_t> &seq) {
        return allow_multiedges ? is_graphical_directed_multi(seq) : is_graphical_directed_simple(seq);
    }

    bool is_graphical_undirected_multi(const vector<vertex_t> &seq) {
        assert(connectivity == connectivity_t::no_restriction);
        const int_t d_sum{ accumulate(seq.begin(), seq.end(), 0LL, [](const int_t x, const vertex_t d) { return x + d.out_degree; }) };
        if (d_sum % 2) {
            return false;
        }

        if (allow_self_loops) {
            return true;
        }
        const int_t d_max{ accumulate(seq.begin(), seq.end(), 0LL, [](const int_t x, const vertex_t d) { return max(x, d.out_degree); }) };

        return d_sum >= 2 * d_max;
    }

    bool is_graphical_undirected_simple_loopy(const vector<vertex_t> &seq) {
        assert(connectivity == connectivity_t::no_restriction);
        vector<int_t> sequence;
        sequence.reserve(seq.size());
        for (const auto [_label, d, _] : seq) {
            sequence.push_back(d);
        }
        sort(sequence.rbegin(), sequence.rend());
        int_t n = static_cast<int_t>(sequence.size());
        range_query_t range_query{ sequence };
        if (range_query(0, n - 1) % 2) {
            return false;
        }
        int_t split_point = n;
        for (int_t k = 1; k <= n; k++) {
            while (split_point > 0 && sequence[split_point - 1] <= k) {
                split_point--;
            }
            auto lhs{ range_query(0, k - 1) };
            auto a{ k * (k + 1) };
            auto b{ max(int_t{ 0 }, (split_point - k) * k) };
            auto c{ range_query(max(split_point, k), n - 1) };
            auto rhs{ a + b + c };

            if (lhs > rhs) {
                return false;
            }
        }
        return true;
    }

    bool is_graphical_undirected_simple_loopless(const vector<vertex_t> &seq) {
        assert(connectivity == connectivity_t::no_restriction || connectivity == connectivity_t::weakly_connected);
        int_t p{ static_cast<int_t>(seq.size()) };
        vector<int_t> num_degs(p);
        int_t d_max{ 0 }, d_min{ p }, d_sum{ 0 }, n{ 0 };
        for (auto [_label, d, _in] : seq) {
            if (d < 0 || d >= p) {
                return false;
            }
            else if (d > 0) {
                n++;
                num_degs[d]++;
            }
            d_max = max(d_max, d);
            d_min = min(d_min, d);
            d_sum = d_sum + d;
        }

        if (connectivity == connectivity_t::weakly_connected && p > 1 && (d_min == 0 || d_sum < 2 * (p - 1))) {
            return false;
        }

        if (d_sum % 2) {
            return false;
        }
        else if (p == 0 or 4 * d_min * p >= (d_max + d_min + 1) * (d_max + d_min + 1)) {
            return true;
        }

        int_t k{ 0 }, sum_deg{ 0 }, sum_ni{ 0 }, sum_ini{ 0 };
        for (int_t d_k = d_max; d_k >= d_min; d_k--) {
            if (d_k < k + 1) {
                return true;
            }
            if (num_degs[d_k] > 0) {
                int_t run_size{ num_degs[d_k] };
                if (d_k < k + run_size) {
                    run_size = d_k - k;
                }
                sum_deg += run_size * d_k;
                for (int_t v = 0; v < run_size; v++) {
                    sum_ni += num_degs[k + v];
                    sum_ini += (k + v) * num_degs[k + v];
                }
                k += run_size;
                if (sum_deg > k * (n - 1) - k * sum_ni + sum_ini) {
                    return false;
                }
            }
        }
        return true;
    }

    bool is_graphical_undirected_simple(const vector<vertex_t> &seq) {
        return allow_self_loops ? is_graphical_undirected_simple_loopy(seq) : is_graphical_undirected_simple_loopless(seq);
    }

    bool is_graphical_undirected(const vector<vertex_t> &seq) {
        return allow_multiedges ? is_graphical_undirected_multi(seq) : is_graphical_undirected_simple(seq);
    }

    bool is_graphical(const vector<vertex_t> &seq) {
        return directed ? is_graphical_directed(seq) : is_graphical_undirected(seq);
    }

    void scc_dfs(const vector<vector<int_t>> &adj, vector<bool>& visited, vector<int_t>& order, int_t u) {
        visited[u] = true;
        for (auto v : adj[u]) {
            if (!visited[v]) {
                scc_dfs(adj, visited, order, v);
            }
        }
        order.push_back(u);
    }

    pair<union_find, vector<int_t>> scc(const vector<vector<int_t>> &adj) {
        int_t n = size(adj), u, v;
        union_find uf(n);
        vector<bool> visited(n);
        vector<int_t> order;
        order.reserve(n);
        vector<int_t> dag;
        vector<vector<int_t>> rev(n);
        for (int_t i = 0; i < n; i++) {
            for (auto j : adj[i]) {
                rev[j].push_back(i);
            }
        }
        for (int_t i = 0; i < n; i++) {
            if (!visited[i]) {
                scc_dfs(rev, visited, order, i);
            }
        }
        fill(visited.begin(), visited.end(), false);
        stack<int_t> S;
        for (int_t i = n-1; i >= 0; i--) {
            if (visited[order[i]]) {
                continue;
            }
            S.push(order[i]);
            dag.push_back(order[i]);
            while (!S.empty()) {
                auto u = S.top();
                visited[u] = true;
                S.pop();
                uf.unite(u, order[i]);
                for (auto v : adj[u]) {
                    if (!visited[v]) {
                        S.push(v);
                    }
                }
            }
        }
        return {uf, dag};
    }

    bool is_strongly_connected(const vector<vector<int_t>>& adj) {
        return scc(adj).first.components == 1;
    }
}

int main(int argc, char **argv) {
    init_io(argc, argv);

    for (int i = 4; i < argc; i++) {
        string s(argv[i]);
        if (s == "directed") {
            directed = true;
        }
        else if (s == "multi") {
            allow_multiedges = true;
        }
        else if (s == "loopy") {
            allow_self_loops = true;
        }
        else if (s == "weakly_connected") {
            connectivity = connectivity_t::weakly_connected;
        }
        else if (s == "strongly_connected") {
            connectivity = connectivity_t::strongly_connected;
        }
    }


    int_t num_vertices, num_edges = 0;
    judge_in >> num_vertices;

    vector<vertex_t> vertices(num_vertices);
    for (int_t i = 0; i < num_vertices; i++) {
        vertices[i].label = i;
    }

    for (auto &v : vertices) {
        judge_in >> v.out_degree;
        num_edges += v.out_degree;
    }

    for (auto &v : vertices) {
        if (directed) {
            judge_in >> v.in_degree;
        }
        else {
            v.in_degree = v.out_degree;
        }
    }
    if (!directed) {
        num_edges /= 2;
    }

    if (!is_graphical(vertices)) {
        string author_possibility;
        author_out >> author_possibility;
        if (author_possibility != "Omogulegt!") {
            wrong_answer("No graph construction is possible but author claims a graph exists.\n");
        }
    }
    else {

        int_t n, m;
        if (!(author_out >> n)) {
            wrong_answer("Failed to read number of vertices.\n");
        }

        if (num_vertices != n) {
            wrong_answer("Incorrect number of vertices. Expected %lld, but got %lld.\n", num_vertices, n);
        }

        if (!(author_out >> m)) {
            wrong_answer("Failed to read number of edges.\n");
        }

        if (num_edges != m) {
            wrong_answer("Incorrect number of edges. Expected %lld, but got %lld.\n", num_edges, m);
        }

        vector<vertex_t> author_vertices(n);
        for (int_t i = 0; i < num_vertices; i++) {
            author_vertices[i].label = i;
        }

        map<pair<int_t, int_t>, int_t> edges;
        union_find uf(n);
        vector<vector<int_t>> adj(n);

        for (int_t i = 1; i <= num_edges; ++i) {
            int_t a, b;

            if (!(author_out >> a >> b)) {
                wrong_answer("Failed to read %lld-th edge in output.\n", i);
            }
            if (a < 1 || n < a) {
                wrong_answer("From-vertex %lld given in edge %lld is out of bounds.\n", a, i);
            }
            if (b < 1 || n < b) {
                wrong_answer("To-vertex %lld given in edge %lld is out of bounds.\n", b, i);
            }
            if (!allow_self_loops && a == b) {
                wrong_answer("Self-loop found in graph in edge %lld, vertex %lld.\n", i, a);
            }

            if (!allow_multiedges) {
                const auto it{ edges.find({ a, b }) };
                if (it != edges.end()) {
                    wrong_answer("Multi-edge found in graph in edge %lld from %lld to %lld, previously seen in edge %lld.\n", i, a, b,
                                 it->second);
                }
            }

            edges.try_emplace({ a, b }, i);
            adj[a-1].push_back(b-1);
            author_vertices[a - 1].out_degree++;
            author_vertices[b - 1].in_degree++;
            uf.unite(a - 1, b - 1);
            if (!directed) {
                edges.try_emplace({ b, a }, i);
                adj[b-1].push_back(a-1);
                author_vertices[b - 1].out_degree++;
                author_vertices[a - 1].in_degree++;
            }
        }

        sort(vertices.begin(), vertices.end());
        sort(author_vertices.begin(), author_vertices.end());

        for (int_t i = 0; i < num_vertices; i++) {
            if (author_vertices[i].out_degree != vertices[i].out_degree || author_vertices[i].in_degree != vertices[i].in_degree) {
                wrong_answer("Mismatch in degrees at judge label %lld and author label %lld, "
                             "expected out-degree %lld and in-degree %lld, but got out-degree %lld and in-degree %lld.\n",
                             vertices[i].label, author_vertices[i].label, vertices[i].out_degree, vertices[i].in_degree,
                             author_vertices[i].out_degree, author_vertices[i].in_degree);
            }
        }

        if (connectivity == connectivity_t::weakly_connected && uf.components != 1) {
            wrong_answer("Graph is not weakly connected.\n");
        }
        else if (connectivity == connectivity_t::strongly_connected && !is_strongly_connected(adj)) {
            wrong_answer("Graph is not strongly connected.\n");
        }
    }

    string s;
    author_out >> ws;
    if (author_out >> s) {
        wrong_answer("Trailing output.\n");
    }
    accept();
}
