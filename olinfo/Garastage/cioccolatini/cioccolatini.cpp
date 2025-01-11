#include <bits/stdc++.h>
using namespace std;

#define LOG 19

vector<vector<int>> adj;
vector<int> C;

vector<int> P;
vector<vector<pair<int, int>>> children;
vector<vector<pair<int, int>>> lift;
vector<int> max_root, depth;

int dfs1(int node, int par, int ma, int d) {
    P[node] = par;
    depth[node] = d;
    max_root[node] = max(ma, C[node]);

    for (auto x: adj[node]) {
        if (x == par) continue;
        children[node].emplace_back(dfs1(x, node, max_root[node], d + 1), x);
    }

    sort(children[node].rbegin(), children[node].rend());

    if (children[node].empty()) return C[node];
    return max(children[node].begin()->first, C[node]);
}

void dfs2(int node) {
    if (node != 0) {
        int ma;
        if (node != children[P[node]][0].second) ma = children[P[node]][0].first;
        else if (children[P[node]].size() > 1) ma = children[P[node]][1].first;
        else ma = -1e9;

        lift[node].emplace_back(P[node], ma);

        for (int i = 0; ; i++) {
            int new_node = lift[node][i].first;
            if (lift[new_node].size() <= i) break;

            lift[node].emplace_back(lift[new_node][i].first, max(lift[node][i].second, lift[new_node][i].second));
        }
    }

    for (auto x: adj[node]) {
        if (x != P[node]) {
            dfs2(x);
        }
    }
}

int query(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    int ma = -1e9;

    if (!children[v].empty()) ma = max(ma, children[v][0].first);

    for (int i = LOG - 1; i >= 0; i--) {
        if (lift[v].size() > i && depth[lift[v][i].first] >= depth[u]) {
            ma = max(ma, lift[v][i].second);
            v = lift[v][i].first;
        }
    }

    if (u == v) {
        if (P[u] != -1) ma = max(ma, max_root[P[u]]);
        
        for (int i = LOG - 1; i >= 0; i--) {
            if (lift[u].size() > i) {
                ma = max(ma, lift[u][i].second);
                u = lift[u][i].first;
            }
        }

        return ma;
    }

    if (!children[u].empty()) ma = max(ma, children[u][0].first);

    for (int i = LOG - 1; i >= 0; i--) {
        if (lift[u].size() > i && lift[u][i].first != lift[v][i].first) {
            ma = max(ma, lift[u][i].second);
            ma = max(ma, lift[v][i].second);
            u = lift[u][i].first;
            v = lift[v][i].first;
        }
    }

    int lca = P[u];

    for (int i = 0; i < children[lca].size(); i++) {
        if (children[lca][i].second != u && children[lca][i].second != v) {
            ma = max(ma, children[lca][i].first);
            break;
        }
    }

    if (P[lca] != -1) ma = max(ma, max_root[P[lca]]);
    for (int i = LOG - 1; i >= 0; i--) {
        if (lift[lca].size() > i) {
            ma = max(ma, lift[lca][i].second);
            lca = lift[lca][i].first;
        }
    }

    return ma;
}

vector<int> raccogli(int N, int Q, vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &L, vector<int> &T) {
    ::C = C;
    adj.resize(N);
    P.resize(N);
    children.resize(N);
    lift.resize(N);
    max_root.resize(N);
    depth.resize(N);

    for (int i = 0; i < N - 1; i++) {
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }

    dfs1(0, -1, -1e9, 0);
    dfs2(0);

    vector<int> ans(Q);
    for (int i = 0; i < Q; i++) ans[i] = query(L[i], T[i]);

    return ans;
}