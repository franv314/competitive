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
        int sum = 0, best_diff = 0;
        for (auto c: adj[node]) {
            if (c == par) continue;
            auto [without, with] = dfs(c, node);

            sum += without;
            best_diff = max(best_diff, with + 1 - without);
        }

        return make_pair(sum + best_diff, sum);
    };

    cout << dfs(0, -1).first << '\n';
}