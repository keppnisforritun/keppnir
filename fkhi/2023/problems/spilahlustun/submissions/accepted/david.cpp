#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<double>
#define ld long double;
#define ii pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vc vector<char>
#define vs vector<string>
#define vd vector<double>
#define vcom vector<com>
#define vld vector<ld>
#define vll vector<ll>
#define vvi vector<vi>
#define vvii vector<vii>
#define vvc vector<vc>
#define vvs vector<vs>
#define vvll vector<vll>
#define vvd vector<vd>
#define vvcom vector<vcom>
#define vvld vector<vld>
#define FOR(x,n) for(int x=0;x<(n);x++)
#define FORS(x,n) for(int x=1;x<=(n);x++)
#define FORE(x,a) for(auto &x: a)
#define FORT(x,a,b) for(int x=(a);x<(b);x++)
#define FORD(x,a,b) for(int x=(a);x>=(b);x--)
#define ALL(x) x.begin(),x.end()
#define REP(n) for(int _ = 0; _ < n; _++)
#define MT make_tuple
#define MP make_pair
#define pb push_back
#define endl '\n'
#define F first
#define S second
#define vvvll vector<vvll>
#define sz(x) ((int)x.size())

struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
    int re = 0;
    int rre = 0;
	Node(int val) : val(val), y(rand()) {}
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

template<class F> void each(Node* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

void rev(Node* t) {
    if(!t) return;
    t->re ^= 1;
    t->rre ^= 1;
}

void prep(Node *n) {
    if(!n) return;
    if(n->re) {
        n->re = 0;
        rev(n->l);
        rev(n->r);
        swap(n->l,n->r);
    }
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
    prep(n);
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
		n->r = pa.first;
		n->recalc();
		return {n, pa.second};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
    prep(l);
    prep(r);
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->recalc();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->recalc();
		return r;
	}
}

Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

void reverse(Node*& t, int l, int r) {
	Node *a, *b, *c;
    tie(a,b) = split(t,l);
    tie(b,c) = split(b,r-l+1);
    
    rev(b);
    t = merge(a,merge(b,c));
}

void solve() {
    int n,k;
    cin >> n >> k;
    Node* r = 0;
    FORS(i,n) {
        r = merge(r,new Node(i));
    }
    FOR(i,k) {
        int s,t;
        cin >> s >> t;
        reverse(r,s-1,t-1);
    }
    FORS(i,n) {
        Node *n = 0;
        tie(n,r) = split(r,1);
        if(n->rre) cout << "-";
        cout << n->val << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    srand(42);
    while(t--) {
        solve();
    }
}