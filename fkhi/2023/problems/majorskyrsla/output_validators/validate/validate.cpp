#include "validate.h"
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int read_user_int() {
    int x;
    if(!(author_out >> x)) {
        wrong_answer("Malformed output, failed to read int.\n");
    }
    return x;
}

ll major(vector<int> &pi) {
    ll sm = 0;
    for(int i = 0; i < pi.size() - 1; ++i)
        if(pi[i] > pi[i + 1])
            sm += i + 1;
    return sm;
}

int main(int argc, char **argv) {
    init_io(argc, argv);
    int n; ll k;
    judge_in >> n >> k;
    vector<int> ans(n);
    for(int i = 0; i < n; ++i) {
        ans[i] = read_user_int();
    }
    string trailing;
    if(author_out >> trailing) {
        wrong_answer("Trailing output.\n");
    }
    if(major(ans) != k) {
        wrong_answer("Incorrect output.\n");
    }
    sort(ans.begin(), ans.end());
    for(int i = 0; i < n; ++i) {
        if(ans[i] != i + 1) {
            wrong_answer("Invalid permutation.\n");
        }
    }
    accept();
}
