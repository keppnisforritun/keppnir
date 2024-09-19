#include <bits/stdc++.h>

using namespace std;
using int_t = int64_t;

constexpr int_t multiplier(const string_view s) {
    if (s == "sekunda" || s == "sekundur") {
        return 1;
    }
    if (s == "minuta" || s == "minutur") {
        return 60 * multiplier("sekunda");
    }
    if (s == "klukkustund" || s == "klukkustundir") {
        return 60 * multiplier("minuta");
    }
    if (s == "dagur" || s == "dagar") {
        return 8 * multiplier("klukkustund");
    }
    if (s == "vika" || s == "vikur") {
        return 5 * multiplier("dagur");
    }
    if (s == "ar") {
        return 52 * multiplier("vika");
    }
    cout << s << endl;
    assert(false);
}

constexpr int_t repetitions_per_year(const string_view s) {
    if (s == "daglega") {
        return multiplier("ar") / multiplier("dagur");
    }
    if (s == "vikulega") {
        return multiplier("ar") / multiplier("vika");
    }
    else {
        return multiplier("ar") / multiplier("ar");
    }
}

int main() {
    string trash;
    int_t repetitions;
    string period;
    cin >> repetitions >> trash >> period;
    repetitions *= 5 * repetitions_per_year(period);

    int_t time_to_do;
    string unit;
    cin >> time_to_do >> unit;
    time_to_do *= multiplier(unit);

    int_t time_to_code;
    cin >> time_to_code >> unit;
    time_to_code *= multiplier(unit);

    const int_t time_saved = time_to_do * repetitions - time_to_code;
    if (time_saved < 0) {
        cout << "Borgar sig ekki!" << endl;
    }
    else {
        cout << time_saved << endl;
    }
    return 0;
}
