#include <bits/stdc++.h>
using namespace std;
using int_t = int64_t;
constexpr int_t INF{numeric_limits<int_t>::max()};
constexpr double EPS{1e-9};
constexpr double pi{M_PI};

template <class T>
T smod(T a, T b)
{
    return (a % b + b) % b;
}

template <size_t N>
struct flow_network
{
    struct edge
    {
        int_t v, cap, nxt;
    };
    array<int_t, N> q{}, d{}, head{}, curh{};
    vector<edge> e, e_store;
    flow_network()
    {
        head.fill(-1);
    }
    void reset()
    {
        e = e_store;
    }
    void add_edge(int_t u, int_t v, int_t uv, int_t vu = 0)
    {
        e.emplace_back(v, uv, head[u]);
        head[u] = ssize(e) - 1;
        e.emplace_back(u, vu, head[v]);
        head[v] = ssize(e) - 1;
    }
    int_t augment(int_t v, int_t t, int_t f)
    {
        if (v == t)
        {
            return f;
        }
        for (auto &i = curh[v]; i != -1; i = e[i].nxt)
        {
            if (e[i].cap > 0 && d[e[i].v] + 1 == d[v])
            {
                if (auto ret = augment(e[i].v, t, min(f, e[i].cap)); ret > 0)
                {
                    e[i].cap -= ret;
                    e[i ^ 1].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int_t max_flow(int_t s, int_t t, bool res = true)
    {
        e_store = e;
        int_t l, r, f = 0, x;
        while (true)
        {
            d.fill(-1);
            int_t l = 0;
            int_t r = 0;
            d[q[r++] = t] = 0;
            while (l < r)
            {
                for (int_t v = q[l++], i = head[v]; i != -1; i = e[i].nxt)
                {
                    if (e[i ^ 1].cap > 0 && d[e[i].v] == -1)
                    {
                        d[q[r++] = e[i].v] = d[v] + 1;
                    }
                }
            }
            if (d[s] == -1)
            {
                break;
            }
            curh = head;
            while ((x = augment(s, t, INF)) != 0)
            {
                f += x;
            }
        }
        if (res)
        {
            reset();
        }
        return f;
    }
};

struct apple_t
{
    int_t strength;
    int_t amount;
    string name;
};

struct doctor_t
{
    int_t strength;
    int_t amount;
    string name;
    set<string> immunities;
};

int main()
{

    int_t L, E;
    cin >> L >> E;

    vector<apple_t> apples(E);
    vector<doctor_t> doctors(L);
    int_t doctor_amount_sum = 0;
    for (auto &[strength, amount, name] : apples)
    {
        cin >> name >> strength >> amount;
    }
    for (auto &[strength, amount, name, immunities] : doctors)
    {
        int_t number_of_immunities;
        cin >> name >> strength >> amount >> number_of_immunities;
        for (int_t i = 0; i < number_of_immunities; i++)
        {
            string s;
            cin >> s;
            immunities.emplace(s);
        }
        doctor_amount_sum += amount;
    }

    auto can_survive = [E, L, doctor_amount_sum, &apples, &doctors](int_t days)
    {
        flow_network<1'024> G;

        const int_t source{E + L};
        const int_t sink{E + L + 1};
        for (int_t i = 0; i < E; i++)
        {
            G.add_edge(source, i, apples[i].amount);
        }

        for (int_t i = 0; i < E; i++)
        {
            for (int_t j = 0; j < L; j++)
            {
                if (apples[i].strength >= doctors[j].strength && !doctors[j].immunities.contains(apples[i].name))
                {
                    G.add_edge(i, E + j, INF);
                }
            }
        }

        for (int_t i = 0; i < L; i++)
        {
            G.add_edge(E + i, sink, doctors[i].amount * days);
        }

        return G.max_flow(source, sink) == doctor_amount_sum * days;
    };

    int_t lo = 1;
    int_t hi = 500LL * 1'000'000'000;
    int_t best = 0;
    while (lo <= hi)
    {
        int_t mid = midpoint(lo, hi);

        if (can_survive(mid))
        {
            lo = mid + 1;
            best = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }

    cout << best << endl;

    return 0;
}
