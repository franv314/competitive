#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int count_sets(int N, vector<int> u, vector<int> v) {
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }

    auto dfs = [&](auto &&dfs, int node, int par = -1) -> pair<int, int> {
        int s = 1, d = 0;

        for (auto x: adj[node]) {
            if (x == par) continue;
            auto [sc, dc] = dfs(dfs, x, node);

            s = s * (sc + 1LL) % MOD;
            d = ((long long)d + sc + dc) % MOD; 
        }

        return {s, d};
    };

    auto [s, d] = dfs(dfs, 0);
    return (s + d) % MOD;
}
