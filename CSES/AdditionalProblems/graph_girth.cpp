#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);

    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<int> dp;
    int ans = 1e9;
    auto dfs = [&](auto &&dfs, int node, int d = 0) -> void {
        bool has_root_edge = false;
        for (auto x: adj[node]) {
            if (dp[x] != -1) {
                if (dp[x] != 0)
                    dp[node] = min(dp[node], 1 + dp[x]);
                else if (d != 1)
                    has_root_edge = true;
            }
        }

        if (has_root_edge) {
            ans = min(ans, 1 + dp[node]);
            dp[node] = 1;
        }

        for (auto x: adj[node]) {
            if (dp[x] == -1) {
                dp[x] = 1 + dp[node];
                dfs(dfs, x, d + 1);
            }
        }
    };

    for (int i = 0; i < N; i++) {
        dp.assign(N, -1);
        dp[i] = 0;
        dfs(dfs, i);
    }

    cout << (ans == 1e9 ? -1 : ans) << '\n';
}
