#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, v; cin >> n >> k >> v;
    v--;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    auto dp = [&](auto &&dp, int node, int d = 0, int par = -1) -> int {
        if (adj[node].size() == 1) return d;
        
        vector<int> children_dp;
        for (auto x: adj[node]) {
            if (x == par) continue;
            auto ch = dp(dp, x, d + 1, node);

            children_dp.push_back(ch);
        }
        if (children_dp.size() == 1) return children_dp[0];
        
        sort(children_dp.begin(), children_dp.end());
        int dst = children_dp[0] + children_dp[1] - 2 * d;
        if (dst - 2 < k) return d;
        return children_dp[0];
    };

    cout << (dp(dp, v) == 0 ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
