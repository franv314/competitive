#include <bits/stdc++.h>
using namespace std;

#define MAXN 300'001
#define MAXLOGN 19

int M, N;
vector<int> adj[MAXN];
vector<pair<int, int>> req;

struct DSU {
    vector<int> nodes;
    int sets;

    int find(int node) {
        while (nodes[node] >= 0)
            node = nodes[node];
        return node;
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        sets--;
        if (nodes[u] < nodes[v]) nodes[v] = u;
        else nodes[u] = v;

    }

    DSU() {}
    DSU(int N) : nodes(N + 1, -1), sets(N) {}
};

int depth[MAXN];
int bin_lift[MAXN][MAXLOGN];
int hp[MAXN];
DSU dsu;

void read_input() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i < N; i++) {
        int t1, t2; cin >> t1 >> t2;
        adj[t1].push_back(t2);
        adj[t2].push_back(t1);
    }

    cin >> M;
    req.resize(M);
    for (int i = 0; i < M; i++) {
        int t1, t2; cin >> t1 >> t2;
        req[i] = {t1, t2};
    }
}

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
        dsu.join(node, bin_lift[node][0]);
    }
    return min_depth;
}

int pow(int e) {
    int ans = 1;
    for (int _ = 0; _ < e; _++) ans = (ans * 2) % 1'000'000'007;
    return ans;
}

int main() {
    read_input();
    
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

        dsu.join(u, v);
        hp[old_u] = min(hp[old_u], depth[u]);
        hp[old_v] = min(hp[old_v], depth[v]);
    }

    dfs2(1);

    cout << pow(dsu.sets - 1) << endl;

    return 0;
}