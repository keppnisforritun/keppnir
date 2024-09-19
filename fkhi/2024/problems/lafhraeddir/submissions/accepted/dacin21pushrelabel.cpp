#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const ll INF = ~(1LL<<63);
typedef vector<int> vi;
typedef vector<vi> vvi;

template<typename flow_t = long long>
struct PushRelabel {
    struct Edge {
        int to, rev;
        flow_t f, c;
    };
    vector<vector<Edge> > g;
    vector<flow_t> ec;
    vector<Edge*> cur;
    vector<vector<int> > hs;
    vector<int> H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}
    void add_edge(int s, int t, flow_t cap, flow_t rcap=0) {
        if (s == t) return;
        Edge a = {t, (int)g[t].size(), 0, cap};
        Edge b = {s, (int)g[s].size(), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);
    }
    void add_flow(Edge& e, flow_t f) {
        Edge &back = g[e.to][e.rev];
        if (!ec[e.to] && f)
            hs[H[e.to]].push_back(e.to);
        e.f += f; e.c -= f;
        ec[e.to] += f;
        back.f -= f; back.c += f;
        ec[back.to] -= f;
    }
    flow_t max_flow(int s, int t) {
        int v = g.size();
        H[s] = v;
        ec[t] = 1;
        vector<int> co(2*v);
        co[0] = v-1;
        for(int i=0;i<v;++i) cur[i] = g[i].data();
        for(auto &e:g[s]) add_flow(e, e.c);
        if(hs[0].size())
        for (int hi = 0;hi>=0;) {
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > 0) // discharge u
                if (cur[u] == g[u].data() + g[u].size()) {
                    H[u] = 1e9;
                    for(auto &e:g[u])
                        if (e.c && H[u] > H[e.to]+1)
                            H[u] = H[e.to]+1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        for(int i=0;i<v;++i)
                            if (hi < H[i] && H[i] < v){
                                --co[H[i]];
                                H[i] = v + 1;
                            }
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->to]+1)
                    add_flow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
            while (hi>=0 && hs[hi].empty()) --hi;
        }
        return -ec[s];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int L, E; cin >> L >> E;
    vector<string> aname(E), dname(L);
    map<string,int> aind;
    vl acnt(E), astr(E), dcnt(L), dstr(L);
    vvi immune(L, vi(E, 0));
    for(int i = 0; i < E; ++i) {
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
        PushRelabel<> fw(E + L + 2);
        for(int i = 0; i < E; ++i) {
            fw.add_edge(E + L, i, acnt[i]);
        }
        __int128_t targ = 0;
        for(int i = 0; i < L; ++i) {
            targ += ((__int128_t) md) * dcnt[i];
            if(targ > E * 1'000'000'000LL) break;
            fw.add_edge(E + i, E + L + 1, md * dcnt[i]);
        }
        if(targ > E * 1'000'000'000LL) {
            hi = md - 1;
            continue;
        }
        for(int i = 0; i < L; ++i) {
            for(int j = 0; j < E; ++j) {
                if(immune[i][j]) continue;
                if(astr[j] < dstr[i]) continue;
                fw.add_edge(j, E + i, INF);
            }
        }
        if(fw.max_flow(E + L, E + L + 1) < targ)
            hi = md - 1;
        else lo = md;
    }
    cout << lo << '\n';
}

