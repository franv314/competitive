#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<int> depth(n, -1);
    vector<vector<int>> intradj(n);
    vector<pair<int, int>> bridges;
    vector<int> bcc(n, -1), bcc_size(n);

    auto dfs = [&](auto &&dfs, int node, int d = 0) -> int {
        depth[node] = d;
        int mi = 1e9;

        for (auto x: adj[node]) {
            if (depth[x] == -1) {
                int mi_child = dfs(dfs, x, d + 1);
                mi = min(mi, mi_child);

                if (mi_child > d) {
                    bridges.emplace_back(node, x);
                } else {
                    intradj[x].push_back(node);
                    intradj[node].push_back(x);
                }
            } else if (depth[x] < d - 1) {
                mi = min(mi, depth[x]);
            }
        }

        return mi;
    };

    auto dfs2 = [&](auto &&dfs2, int node, int root) -> void {
        bcc[node] = root;
        bcc_size[root]++;

        for (auto x: intradj[node]) {
            if (bcc[x] == -1) {
                dfs2(dfs2, x, root);
            }
        }
    };

    dfs(dfs, 0);
    for (int i = 0; i < n; i++)
        if (bcc[i] == -1)
            dfs2(dfs2, i, i);

    vector<vector<int>> bridgeadj(n);
    for (auto [u, v]: bridges) {
        bridgeadj[bcc[u]].push_back(bcc[v]);
        bridgeadj[bcc[v]].push_back(bcc[u]);
    }

    auto dfs3 = [&](auto &&dfs3, int node, int par = -1) -> pair<int, long long> {
        int size = bcc_size[node];
        long long best_ans = 1e18;

        for (auto x: bridgeadj[node]) {
            if (x == par) continue;
            auto [sz, ans] = dfs3(dfs3, x, node);
            size += sz;
            best_ans = min(best_ans, ans);
        }

        best_ans = min(best_ans, (long long)size * (size - 1) / 2 + (long long)(n - size) * (n - size - 1) / 2);
        return {size, best_ans};
    };

    cout << dfs3(dfs3, 0).second << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}