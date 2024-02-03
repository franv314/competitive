#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Info {
    int top;
    i64 len, sum, min, pref, suff, sub;

    Info(int top, i64 len, i64 sum, i64 min, i64 pref, i64 suff, i64 sub) :
        top(top), len(len), sum(sum), min(min), pref(pref), suff(suff), sub(sub) { }
    Info(int top, int val) :
        Info(top, 1, val, val, max(0, val), max(0, val), max(0, val)) { }
    Info() :
        Info(-1, 0, 0, 1e18, 0, 0, 0) { }
};

Info merge(const Info &a, const Info &b) {
    return {
        b.top,
        a.len + b.len,
        a.sum + b.sum,
        min(a.min, b.min),
        max(a.pref, a.sum + b.pref),
        max(b.suff, b.sum + a.suff),
        max({a.sub, b.sub, a.suff + b.pref})
    };
}

vector<vector<pair<int, int>>> adj;
vector<vector<Info>> lift;
vector<int> depth;

void dfs(int node, int par, int par_w) {
    if (par != -1) {
        depth[node] = depth[par] + 1;

        lift[node].emplace_back(par, par_w);
        for (int i = 0; lift[lift[node][i].top].size() > i; i++) {
            lift[node].push_back(merge(lift[node][i], lift[lift[node][i].top][i]));
        }
    }

    for (auto [x, w]: adj[node]) {
        if (x == par) continue;
        dfs(x, node, w);
    }
}

Info query(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    Info iu, iv;
    
    for (int i = lift[v].size() - 1; i >= 0; i--) {
        if (lift[v].size() > i && depth[lift[v][i].top] >= depth[u]) {
            iv = merge(iv, lift[v][i]);
            v = lift[v][i].top;
        }
    }

    if (u == v) return iv;

    for (int i = lift[u].size() - 1; i >= 0; i--) {
        if (lift[u].size() > i && lift[u][i].top != lift[v][i].top) {
            iu = merge(iu, lift[u][i]);
            iv = merge(iv, lift[v][i]);

            u = lift[u][i].top;
            v = lift[v][i].top;
        }
    }

    iu = merge(iu, lift[u][0]);
    iv = merge(iv, lift[v][0]);
    
    swap(iu.pref, iu.suff);
    return merge(iv, iu);
}

void inizia(int N, int T, int A[], int B[], int C[]) {
	adj.resize(N);
    lift.resize(N);
    depth.resize(N);
    for (int i = 0; i < N - 1; i++) {
        adj[A[i]].emplace_back(B[i], C[i]);
        adj[B[i]].emplace_back(A[i], C[i]);
    }

    dfs(0, -1, -1);
}

i64 distanza1(int u, int v) { return query(u, v).len; }
i64 distanza2(int u, int v) { return query(u, v).sum; }
i64 minimo(int u, int v) { return query(u, v).min; }
i64 massimo(int u, int v) { return query(u, v).sub; }
