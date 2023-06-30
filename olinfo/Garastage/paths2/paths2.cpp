#include <bits/stdc++.h>
using namespace std;

#define MAXN 300'001
#define MAXLOGN 19

struct DSU {
    vector<int> nodes, inverts;
    bool zero;
    int sets;

    int find(int node) {
        if (nodes[node] < 0)
            return node;
        return nodes[node] = find(nodes[node]);
    }

    void join(int u, int v, bool same) {
        bool sameness = inverts[u] == inverts[v];
        u = find(u), v = find(v);
        if (u == v) {
            if (sameness != same) zero = true;
            return;
        }

        sets--;
        if (nodes[u] < nodes[v]) {
            nodes[v] = u;
            if (sameness != same) inverts[v] = -1;
        } else {
            nodes[u] = v;
            if (sameness != same) inverts[u] = -1;
        }
    }

    DSU() {}
    DSU(int N) : nodes(N + 1, -1), inverts(N + 1, 1), sets(N), zero(false) {}
};

vector<int> adj[MAXN];
vector<pair<int, int>> req;
int depth[MAXN], hp[MAXN];
int bin_lift[MAXN][MAXLOGN];
DSU dsu;

void dfs(vector<int> &path, int d) {
    int node = path.back();
    depth[node] = d;
    
    for (int i = 0; (1 << i) <= path.size(); i++) {
        bin_lift[node][i] = path[path.size() - 1 - (1 << i)];
    }

    vector<int> new_adj;
    for (auto child: adj[node]) {
        if (!depth[child]) {
            new_adj.push_back(child);
            
            path.push_back(child);
            dfs(path, d + 1);
        }
    }
    adj[node] = new_adj;
    path.pop_back();
}

int dfs2(int node) {
    int min_depth = hp[node];
    for (auto child: adj[node]) {
        min_depth = min(min_depth, dfs2(child));
    }
    if (min_depth < depth[node]) {
        dsu.join(node, bin_lift[node][0], true);
    }
    return min_depth;
}

int pow(int e) {
    int ans = 1;
    for (int i = 0; i < e; i++) ans = (ans * 2) % 1'000'000'007;
    return ans;
}

int count_orientations(int N, int M, vector<int> X, vector<int> Y, vector<int> A, vector<int> B) {
    for (int i = 0; i < N - 1; i++) {
        adj[X[i] + 1].push_back(Y[i] + 1);
        adj[Y[i] + 1].push_back(X[i] + 1);
    }
    for (int i = 0; i < M; i++) {
        req.push_back({A[i] + 1, B[i] + 1});
    }
    
    vector<int> path(1, 1);
    dfs(path, 1);
    depth[0] = -1;

    dsu = DSU(N);
    for (int i = 1; i <= N; i++) hp[i] = depth[i];

    for (auto [u, v]: req) {
        if (depth[v] > depth[u]) swap(u, v);
        int old_u = u, old_v = v;

        for (int i = MAXLOGN - 1; i >= 0; i--) {
            if (depth[bin_lift[u][i]] > depth[v]) {
                u = bin_lift[u][i];
            }
        }

        if (bin_lift[u][0] == v) {
            hp[old_u] = min(hp[old_u], depth[u]);
            continue;
        }

        if (depth[u] != depth[v]) u = bin_lift[u][0];

        for (int i = MAXLOGN - 1; i >= 0; i--) {
            if (bin_lift[u][i] && bin_lift[v][i] && bin_lift[u][i] != bin_lift[v][i]) {
                u = bin_lift[u][i], v = bin_lift[v][i];
            }
        }

        dsu.join(u, v, false);
        hp[old_u] = min(hp[old_u], depth[u]);
        hp[old_v] = min(hp[old_v], depth[v]);
    }

    dfs2(1);

    if (dsu.zero) return 0;
    return pow(dsu.sets - 1);
}