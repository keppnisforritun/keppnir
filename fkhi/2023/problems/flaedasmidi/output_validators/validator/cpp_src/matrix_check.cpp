#include "validate.h"
#include <vector>
#include <Eigen/SparseCore>
#include <Eigen/SparseLU>
using namespace std;

int read_user_int() {
    int x;
    if(!(author_out >> x)) {
        wrong_answer("Malformed output, failed to read int.\n");
    }
    return x;
}

constexpr int max_out = 50000;

int main(int argc, char **argv) {
    init_io(argc, argv);
    int n, m;
    judge_in >> n >> m;
    int v = read_user_int(), e = read_user_int();
    if(v < n + m) {
        wrong_answer("Too few vertices.\n");
    }
    if(e <= 0) {
        wrong_answer("Too few edges.\n");
    }
    if(v > max_out) {
        wrong_answer("Too many vertices.\n");
    }
    if(e > max_out) {
        wrong_answer("Too many edges.\n");
    }
    vector<vector<int>> in_edges(v, vector<int>());
    vector<vector<int>> out_edges(v, vector<int>());
    vector<int> edge_from(e), edge_to(e);
    for(int i = 0; i < e; ++i) {
        int a = read_user_int(), b = read_user_int();
        if(a <= 0 || b <= 0 || a > v || b > v) {
            wrong_answer("Vertex index out of bounds at edge " + to_string(i) + ".\n");
        }
        edge_from[i] = a - 1;
        edge_to[i] = b - 1;
        out_edges[a - 1].push_back(i);
        in_edges[b - 1].push_back(i);
    }
    string trailing;
    if(author_out >> trailing) {
        wrong_answer("Trailing output.\n");
    }
    for(int i = n; i < n + m; ++i) {
        if(out_edges[i].size() > 0) {
            wrong_answer("Edge out of sink " + to_string(i) + ".\n");
        }
    }
    for(int i = 0; i < v; ++i) {
        if(in_edges[i].size() > 2) {
            wrong_answer("Invalid indegree at vertex " + to_string(i) + ".\n");
        }
        if(out_edges[i].size() > 2) {
            wrong_answer("Invalid outdegree at vertex " + to_string(i) + ".\n");
        }
        if(i >= n + m && out_edges[i].empty() && in_edges[i].size() > 0) {
            wrong_answer("Vertex " + to_string(i) + " is a dead end.\n");
        }
    }
    vector<Eigen::Triplet<double>> coeff;
    Eigen::VectorXd b(e);
    for(int i = 0; i < e; ++i) {
        double cf = 1.0 / out_edges[edge_from[i]].size();
        for(int j : in_edges[edge_from[i]]) coeff.emplace_back(i, j, -cf);
        coeff.emplace_back(i, i, 1.0);
        if(edge_from[i] < n) b[i] = cf;
    }
    Eigen::SparseMatrix<double> A(e, e);
    A.setFromTriplets(coeff.begin(), coeff.end());
    Eigen::SparseLU<Eigen::SparseMatrix<double>> lu(A);
    Eigen::VectorXd x = lu.solve(b);
    vector<double> sink_res(m);
    for(int i = 0; i < e; ++i) {
        if(x[i] > 1 + 1e-7) {
            wrong_answer("Overflow at edge " + to_string(i) + ".\n");
        }
        if(edge_to[i] >= n && edge_to[i] < n + m) {
            sink_res[edge_to[i] - n] += x[i];
        }
    }
    for(int i = 0; i < m; ++i) {
        double ex = n; ex /= m;
        if(abs(sink_res[i] - ex) > 1e-7) {
            wrong_answer("Incorrect outflow " + to_string(x[i]) + " at sink " + to_string(i + n) + ".\n");
        }
    }
    accept();
}
