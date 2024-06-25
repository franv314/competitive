#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<array<int, 2>> edges(m);
    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        edges[i] = {u, v};
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }

    vector<array<int, 2>> orient(m);
    vector<bool> is_bridge(m);
    vector<int> depth(n, -1);

    auto dfs = [&](auto &&dfs, int node, int d = 0) -> int {
        depth[node] = d;
        int mi = 1e9;
        for (auto [x, idx]: adj[node]) {

            if (depth[x] != -1 && depth[x] < d - 1) {
                mi = min(mi, depth[x]);
                orient[idx] = {node, x};
            } else if (depth[x] == -1) {
                int mi_child = dfs(dfs, x, d + 1);
                mi = min(mi, mi_child);

                is_bridge[idx] = mi_child > d;
                orient[idx] = {node, x};
            }
        }

        return mi;
    };

    dfs(dfs, 0);

    vector<int> bcc(n, -1), bcc_size(n);
    auto dfs1 = [&](auto &&dfs1, int node, int root) -> void {
        bcc[node] = root;
        bcc_size[root]++;

        for (auto [x, idx]: adj[node])
            if (bcc[x] == -1 && !is_bridge[idx])
                dfs1(dfs1, x, root);
    };

    for (int i = 0; i < n; i++)
        if (bcc[i] == -1)
            dfs1(dfs1, i, i);

    int max_bcc = max_element(bcc_size.begin(), bcc_size.end()) - bcc_size.begin();

    vector<vector<pair<int, int>>> bcc_adj(n);
    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) {
            bcc_adj[bcc[edges[i][0]]].emplace_back(bcc[edges[i][1]], i);
            bcc_adj[bcc[edges[i][1]]].emplace_back(bcc[edges[i][0]], i);
        }
    }

    auto dfs2 = [&](auto &&dfs2, int node, int par = -1) -> void {
        for (auto [x, idx]: bcc_adj[node]) {
            if (x != par) {
                if (bcc[orient[idx][0]] == node) swap(orient[idx][0], orient[idx][1]);
                dfs2(dfs2, x, node);
            }
        }
    };

    dfs2(dfs2, max_bcc);
    cout << bcc_size[max_bcc] << '\n';
    for (auto [u, v]: orient) {
        cout << u + 1 << ' ' << v + 1 << '\n';
    }
}