#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a, b; cin >> n >> a >> b;
    a--, b--;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<int> dista(n), distb(n), furthest(n);
    vector<multiset<int>> dp(n);

    auto dfsa = [&](auto &&dfsa, int node, int par, int d = 0) -> void {
        dista[node] = d;

        for (auto x: adj[node]) {
            if (x != par) {
                dfsa(dfsa, x, node, d + 1);
            }
        }
    };
    
    auto dfsb = [&](auto &&dfsb, int node, int par, int d = 0) -> void {
        distb[node] = d;

        for (auto x: adj[node]) {
            if (x != par) {
                dfsb(dfsb, x, node, d + 1);
            }
        }
    };

    auto dfs1 = [&](auto &&dfs1, int node, int par) -> void {
        dp[node].insert(0);
        for (auto x: adj[node]) {
            if (x != par) {
                dfs1(dfs1, x, node);
                dp[node].insert(1 + *dp[x].rbegin());
            }
        }
    };

    auto dfs2 = [&](auto &&dfs2, int node, int par) -> void {
        int mybest, parval;
        if (node != 0) {
            mybest = *dp[node].rbegin();
            dp[par].erase(dp[par].find(1 + mybest));
            parval = *dp[par].rbegin();
            dp[node].insert(1 + parval);
        }

        furthest[node] = *dp[node].rbegin();

        for (auto x: adj[node]) {
            if (x != par) {
                dfs2(dfs2, x, node);
            }
        }

        if (node != 0) {
            dp[node].erase(dp[node].find(1 + parval));
            dp[par].insert(1 + mybest);
        }
    };

    dfsa(dfsa, a, -1);
    dfsb(dfsb, b, -1);
    dfs1(dfs1, 0, -1);
    dfs2(dfs2, 0, -1);

    auto mergedist = [&](int dista, int distb) {
        int ans = max(dista, distb);
        if (distb % 2 != ans % 2) ans++;
        return ans;
    };
 
    int best = 1e9;
    for (int i = 0; i < n; i++) {
        best = min(best, 2 * (n - 1) - furthest[i] + mergedist(dista[i], distb[i]));
    }

    cout << best << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}