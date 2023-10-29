#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    function<pair<int, int>(int, int)> dfs = [&](int node, int par) {
        int ma_d = 0, ma_l = 0;

        for (auto c: adj[node]) {
            if (c == par) continue;

            auto [c_path, r_path] = dfs(c, node);
            ma_l = max({ma_l, c_path, r_path + ma_d});
            ma_d = max(ma_d, r_path);
        }

        return make_pair(ma_l, 1 + ma_d);
    };

    cout << dfs(0, -1).first << '\n';
}