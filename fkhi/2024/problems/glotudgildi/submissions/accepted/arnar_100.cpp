#include <bits/stdc++.h>

using namespace std;
using int_t = int64_t;

int_t snoob(int_t x) {
    int_t y = x & -x, z = x + y;
    return z | ((x ^ z) >> 2) / y;
}

using state_t = vector<int_t>;
map<state_t, __int128_t> mem;

__int128_t dp(vector<int_t> state) {
    ranges::sort(state);
    const int_t n = ssize(state);
    if (state.empty())
        return 1;
    if (state.front() < 0)
        return 0;
    if (state.back() >= n)
        return 0;
    if (const auto it = mem.find(state); it != end(mem)) {
        return it->second;
    }
    if (state.back() == n - 1) {
        auto next_state = state;
        next_state.pop_back();
        return mem[state] = dp(next_state);
    }

    __int128_t result{ 0 };
    const int_t losses{ n - 1 - state.back() };
    for (int_t mask = (1 << losses) - 1; mask < (1 << n - 1); mask = snoob(mask)) {
        auto next_state{ state };
        next_state.pop_back();
        for (int_t i = 0; i < n - 1; i++) {
            if ((1 << i) & mask) {
                next_state[i]--;
            }
        }
        result += dp(next_state);
    }
    return mem[state] = result;
}

std::ostream &operator<<(std::ostream &dest, __int128_t value) {
    std::ostream::sentry s(dest);
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = std::end(buffer);
        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

int main() {
    int_t n;
    cin >> n;

    vector<int_t> initial(n);
    for (auto &x : initial) {
        cin >> x;
    }

    cout << dp(initial) << endl;
    return 0;
}
