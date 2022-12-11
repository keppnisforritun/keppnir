#include "validate.h"
#include <algorithm>
#include <set>
#include <map>
using namespace std;

const int MAX_LINES = 200000;

int main(int argc, char **argv) {
    init_io(argc, argv);

    int n, m, k;
    judge_in >> n >> m >> k;

    set<string> remaining;
    for (int i = 0; i < k; i++) {
        string item;
        judge_in >> item;
        remaining.insert(item);
    }

    map<string, set<string> > adj;
    for (int i = 0; i < m; i++) {
        string a, b, c;
        judge_in >> a >> b >> c;
        adj[a].insert(b);
        if (c == "open") {
            adj[b].insert(a);
        }
    }

    string judge_start, judge_last, judge_tmp;
    judge_ans >> judge_start;
    assert(judge_start == "1" || judge_start == "impossible");
    while (judge_ans >> judge_tmp) {
        judge_last = judge_tmp;
    }

    string author_start;
    if (!(author_out >> author_start)) {
        wrong_answer("Empty output\n");
    }

    transform(author_start.begin(), author_start.end(), author_start.begin(), ::tolower);

    bool possible = true;
    if (author_start == "1") {
        if (judge_start != "1") {
            wrong_answer("Author claims possible, but no solution exists\n");
        }
    } else if (author_start == "impossible") {
        possible = false;
        if (judge_start != "impossible") {
            wrong_answer("Author claims impossible, but solution exists\n");
        }
    } else {
        wrong_answer("Invalid start node %s\n", author_start.c_str());
    }

    if (possible) {
        string current = author_start, next;
        int count = 1;
        while (author_out >> next) {
            if (++count > MAX_LINES) {
                wrong_answer("Solution too long\n");
            }

            if (adj[current].find(next) == adj[current].end()) {
                wrong_answer("Invalid move from node %s to node %s\n", current.c_str(), next.c_str());
            }

            remaining.erase(next);
            current = next;
        }

        if (current != judge_last) {
            wrong_answer("Invalid end node %s\n", current.c_str());
        }

        if (!remaining.empty()) {
            wrong_answer("Not all required vertices visited\n");
        }
    }

    /* Check for trailing output. */
    string trash;
    if (author_out >> trash) {
        wrong_answer("Trailing output\n");
    }

    accept();
}
