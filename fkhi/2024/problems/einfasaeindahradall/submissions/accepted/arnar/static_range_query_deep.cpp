#include <array>
#include <iostream>
#include <utility>
#include <vector>

#include "constexpr_for.h"
#include "multi_dimensional_vector.h"
#include "static_range_query.h"

using namespace std;
using int_t = int32_t;

template <size_t Dims>
constexpr void solve()
{
    array<size_t, Dims> sizes{};
    array<int_t, Dims> lower{};
    array<int_t, Dims> upper{};

    constexpr_for<0ul, Dims, 1ul>([&sizes, &lower, &upper](auto i) {
        cin >> lower[i] >> upper[i];
        sizes[i] = static_cast<size_t>(upper[i] - lower[i] + 1);
    });

    multi_dimensional_vector<int_t, Dims> arr(sizes);

    int_t m;
    cin >> m;
    array<size_t, Dims> indices{};
    for (int_t i = 0; i < m; i++)
    {
        constexpr_for<0ul, Dims, 1ul>([&indices, &lower](auto i) {
            int_t ind;
            cin >> ind;
            indices[i] = static_cast<size_t>(ind - lower[i]);
        });
        arr[indices] += 1;
    }

    range_query_t range_query{arr};

    int_t q;
    cin >> q;
    for (int_t i = 0; i < q; i++)
    {
        array<size_t, Dims> indices_lower{}, indices_upper{};
        bool external = false;
        constexpr_for<0ul, Dims, 1ul>([&external, &indices_lower, &indices_upper, &lower, &upper](auto i)  {
            int_t ind;
            cin >> ind;
            indices_lower[i] = static_cast<size_t>(min(max(ind, lower[i]), upper[i]) - lower[i]);
            external |= ind > upper[i];
            cin >> ind;
            indices_upper[i] = static_cast<size_t>(min(max(ind, lower[i]), upper[i]) - lower[i]);
            external |= ind < lower[i];
        });

        cout << (external ? 0 : range_query(indices_lower, indices_upper)) << endl;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    size_t dims;
    cin >> dims;
    switch (dims)
    {
    case 1ul:
        solve<1ul>();
        break;
    case 2ul:
        solve<2ul>();
        break;
    case 3ul:
        solve<3ul>();
        break;
    case 4ul:
        solve<4ul>();
        break;
    case 5ul:
        solve<5ul>();
        break;
    case 6ul:
        solve<6ul>();
        break;
    case 7ul:
        solve<7ul>();
        break;
    case 8ul:
        solve<8ul>();
        break;
    case 9ul:
        solve<9ul>();
        break;
    case 10ul:
        solve<10ul>();
        break;
    default:
        __builtin_unreachable();
        break;
    }

    return 0;
}
