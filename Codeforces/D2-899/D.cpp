#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    vector<vector<int>> adj(n);

    for (auto &x: p) cin >> x;

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<long long> cost(n);
    vector<int> sizes(n);
    vector<long long> ans(n);

    function<void(int, int)> dfs1 = [&](int node, int par) {
        sizes[node] = 1;
        for (auto &n: adj[node]) {
            if (n == par) continue;
            dfs1(n, node);
            sizes[node] += sizes[n];
            cost[node] += cost[n];
        }

        if (node != 0) cost[node] += sizes[node] * (long long)(p[node] ^ p[par]);
    };

    function<void(int, int)> dfs2 = [&](int node, int par) {
        long long old_cost_node = cost[node];
        long long old_cost_par = cost[par];
        int old_size_node = sizes[node];
        int old_size_par = sizes[par];

        if (node != 0) {
            cost[par] -= cost[node];
            cost[node] -= sizes[node] * (long long)(p[node] ^ p[par]);
            sizes[par] = n - sizes[node];
            sizes[node] = n;
            cost[par] += sizes[par] * (long long)(p[node] ^ p[par]);
            cost[node] += cost[par];
        }

        ans[node] = cost[node];

        for (auto n: adj[node]) {
            if (n == par) continue;
            dfs2(n, node);
        }

        cost[node] = old_cost_node;
        cost[par] = old_cost_par;
        sizes[node] = old_size_node;
        sizes[par] = old_size_par;
    };

    dfs1(0, -1);
    dfs2(0, -1);

    for (auto a: ans) cout << a << " "; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}