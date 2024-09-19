#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void add_edge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int L, EE; cin >> L >> EE;
    vector<string> aname(EE), dname(L);
    map<string,int> aind;
    vl acnt(EE), astr(EE), dcnt(L), dstr(L);
    vvi immune(L, vi(EE, 0));
    for(int i = 0; i < EE; ++i) {
        cin >> aname[i] >> astr[i] >> acnt[i];
        aind[aname[i]] = i;
    }
    for(int i = 0; i < L; ++i) {
        cin >> dname[i] >> dstr[i] >> dcnt[i];
        int k; cin >> k;
        for(int j = 0; j < k; ++j) {
            string cur; cin >> cur;
            immune[i][aind[cur]] = 1;
        }
    }
    ll lo = 0, hi = 1'000'000'000'000;
    while(hi > lo) {
        ll md = hi - (hi - lo) / 2;
        Dinic fw(EE + L + 2);
        for(int i = 0; i < EE; ++i) {
            fw.add_edge(EE + L, i, acnt[i]);
        }
        __int128_t targ = 0;
        for(int i = 0; i < L; ++i) {
            targ += ((__int128_t) md) * dcnt[i];
            if(targ > EE * 1'000'000'000LL) break;
            fw.add_edge(EE + i, EE + L + 1, md * dcnt[i]);
        }
        if(targ > EE * 1'000'000'000LL) {
            hi = md - 1;
            continue;
        }
        for(int i = 0; i < L; ++i) {
            for(int j = 0; j < EE; ++j) {
                if(immune[i][j]) continue;
                if(astr[j] < dstr[i]) continue;
                fw.add_edge(j, EE + i, acnt[j]);
            }
        }
        if(fw.calc(EE + L, EE + L + 1) < targ)
            hi = md - 1;
        else lo = md;
    }
    cout << lo << '\n';
}

