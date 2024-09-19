#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
using int_t = int64_t;
using section_t = pair<int_t, string>;

int main() {
    string content;
    cin >> content;

    map<string, int_t> counter;
    for (size_t i = 0; i < content.size(); i++) {
        string section;
        for (size_t j = i; j < content.size(); j++) {
            section += content[j];
            counter[section]++;
        }
    }
    vector<section_t> output;
    output.reserve(content.size() * content.size());
    for (auto& [key, value] : counter) {
        output.emplace_back(-value, key);
    }
    sort(output.begin(), output.end());
    for (auto& [occurrences, subcontent] : output) {
        cout << -occurrences << " " << subcontent << endl;
    }
    
    return 0;
}
