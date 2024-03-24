#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto &&dfs, int node, int par, int x) -> pair<int, int> {
        pair<int, int> ans = {0, 1};
        for (auto y: adj[node]) {
            if (y == par) continue;
            auto [full, rem] = dfs(dfs, y, node, x);
            ans.first += full;
            ans.second += rem;
        }

        if (ans.second >= x) {
            ans.first++;
            ans.second = 0;
        }
        return ans;
    };

    int l = 1, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        
        pair<int, int> test = dfs(dfs, 0, -1, m);

        if (test.first > k) l = m;
        else r = m;
    }

    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}