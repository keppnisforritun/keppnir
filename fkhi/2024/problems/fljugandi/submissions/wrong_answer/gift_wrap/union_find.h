#pragma once
#include <numeric>
#include <vector>

struct union_find {
    std::size_t n;
    std::vector<std::size_t> parent;
    union_find(std::size_t n) : n(n), parent(n) {
        std::iota(begin(parent), end(parent), std::size_t{});
    }
    std::size_t find(std::size_t x) {
        return parent[x] = parent[x] == x ? x : find(parent[x]);
    }
    bool unite(std::size_t x, std::size_t y) {
        const auto xp{ find(x) };
        const auto yp{ find(y) };
        if (yp == xp) {
            return false;
        }
        parent[yp] = xp;
        return true;
    }
    bool united(std::size_t x, std::size_t y) {
        return find(x) == find(y);
    }
};
