#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<bool> is_leaf(n), is_f_leaf(n);

    for (int i = 0; i < n; i++) {
        is_leaf[i] = adj[i].size() == 1;
        is_f_leaf[i] = false;

        for (auto x: adj[i])
            is_f_leaf[i] = is_f_leaf[i] || adj[x].size() == 1;
    }

    int leaves = count(is_leaf.begin(), is_leaf.end(), true);
    int f_leaves = count(is_f_leaf.begin(), is_f_leaf.end(), true);

    i64 ans = leaves * (i64)(n - leaves);

    auto dfs = [&](auto &&dfs, int node, int par = -1) -> tuple<int, int, int> {
        vector<tuple<int, int, int, int>> subtrees;
        int t_size = 0, t_leaf = 0, t_f_leaf = 0;

        for (auto x: adj[node]) {
            if (x == par) continue;
            auto [c_size, c_leaf, c_f_leaf] = dfs(dfs, x, node);

            t_size += c_size;
            t_leaf += c_leaf;
            t_f_leaf += c_f_leaf;

            subtrees.emplace_back(x, c_size, c_leaf, c_f_leaf);
        }

        t_size += 1;
        t_leaf += is_leaf[node];
        t_f_leaf += is_f_leaf[node];

        if (par != -1)
            subtrees.emplace_back(par, n - t_size, leaves - t_leaf, f_leaves - t_f_leaf);

        if (is_f_leaf[node]) {
            for (auto [x, s, l, fl]: subtrees) {
                if (is_leaf[x]) continue;

                int size_out = n - 1 - s;
                int leaf_out = leaves - is_leaf[node] - l;
                int f_leaf_out = f_leaves - is_f_leaf[node] - fl;

                int good = size_out - leaf_out - f_leaf_out;
                
                ans += good;
            }
        }

        return {t_size, t_leaf, t_f_leaf};
    };

    dfs(dfs, 0);

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
