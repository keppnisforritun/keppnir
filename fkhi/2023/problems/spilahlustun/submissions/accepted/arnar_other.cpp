#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);

const double EPS = 1e-9;
const double pi = acos(-1);
typedef unsigned long long ull;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
template <class T> T smod(T a, T b) {
    return (a % b + b) % b;
}


template<typename T>
class splay_tree {
public:
    struct node {
        node *left, *right;
        node *parent;
        T key;
        bool reversed;
        size_t p_size;
        void push() {
            if (reversed) {
                if (left) left->reversed = !left->reversed;
                if (right) right->reversed = !right->reversed;
                reversed = false;
                key = -key;
                swap(left, right);
            }
        }
        void recompute_size() {
            p_size = 1 + (left ? left->p_size : 0ull) + (right ? right->p_size : 0ull);
        }
        node(const T& init = T()) : left(nullptr), right(nullptr), parent(nullptr), key(init), reversed(false), p_size(0ull) { }
        ~node() {
        }
    } *root;

    void left_rotate(node *x) {
        node *y = x->right;
        if (y) {
            x->right = y->left;
            if (y->left) y->left->parent = x;
            y->parent = x->parent;
        }

        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) y->left = x;
        if(x->parent) x->parent->recompute_size();
        x->recompute_size();
        y->recompute_size();
        x->parent = y;

    }

    void right_rotate(node *x) {
        node *y = x->left;
        if (y) {
            x->left = y->right;
            if (y->right) y->right->parent = x;
            y->parent = x->parent;
        }
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) y->right = x;
        if(x->parent) x->parent->recompute_size();
        x->recompute_size();
        y->recompute_size();
        x->parent = y;
    }

    void splay(node *x) {
        while (x->parent) {
            if (!x->parent->parent) {
                if (x->parent->left == x) right_rotate(x->parent);
                else left_rotate(x->parent);
            } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
                right_rotate(x->parent->parent);
                right_rotate(x->parent);
            } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
                left_rotate(x->parent->parent);
                left_rotate(x->parent);
            } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
                right_rotate(x->parent);
                left_rotate(x->parent);
            } else {
                left_rotate(x->parent);
                right_rotate(x->parent);
            }
        }
    }

    void inorder(node *u) const {
        if (u) {
            u->push();
            auto left = u->left;
            auto right = u->right;
            inorder(left);
            cout << u->key << " ";
            inorder(right);
        }
    }
    splay_tree() : root(nullptr) { }

    void insert(const T &key) {
        node *z = root;
        node *p = nullptr;

        while (z) {
            z->push();
            p = z;
            z = z->right;
        }

        z = new node(key);
        z->parent = p;
        if (!p) root = z;
        else p->right = z;

        splay(z);
    }

    splay_tree split(const T &k) {
        splay_tree other;
        node *z = kth_node(k);
        if (!z) return other;

        splay(z);

        other.root = z->right;
        z->right = nullptr;
        z->recompute_size();
        if (!other.empty()) other.root->parent = nullptr;
        return other;
    }

    void join(splay_tree &other) {
        if (!other.root) {
            return;
        }
        if (!root) {
            root = other.root;
        }
        else {
            node* n = kth_node(root->p_size-1);
            splay(n);
            root->right = other.root;
            root->right->parent = root;
            root->recompute_size();
        }
    }

    void reverse(int i, int j) {
        if (i == 0) {
            splay_tree right = split(j);
            root->reversed = !root->reversed;
            join(right);
        }
        else {
            splay_tree middle = split(i-1);
            splay_tree right = middle.split(j-i);
            middle.root->reversed = !middle.root->reversed;
            middle.join(right);
            join(middle);
        }
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    node* kth_node(size_t k) {
        node *z = root;
        while (z) {
            z->push();
            size_t left_size = z->left ? z->left->p_size : 0;
            if (k == left_size) {
                return z;
            }
            if (k < left_size) {
                z = z->left;
            }
            else {
                z = z->right;
                k -= (left_size + 1);
            }
        }
        return z;
    }

    bool empty() const { return root == nullptr; }
    size_t size() const { return root ? root->p_size : 0ull; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    
    int n, q;
    cin >> n >> q;

    splay_tree<int> tree;
    for (int i = 0; i < n; i++) {
        tree.insert(i+1);
    }
    

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        tree.reverse(a, b);
    }

    tree.inorder();

    return 0;
}
