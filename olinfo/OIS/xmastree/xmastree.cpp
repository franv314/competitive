#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> A(N);
    vector<vector<int>> adj(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (auto &a: A) cin >> a;

    function<pair<long long, long long>(int, int)> dfs = [&](int node, int par) {
        bool parity = 0;
        long long sum = 0, best_diff = 1e18;

        for (auto &c: adj[node]) {
            if (c == par) continue;
            auto [odd, even] = dfs(c, node);
            sum += max(odd, even);
            best_diff = min(best_diff, abs(odd - even));
            parity ^= (odd >= even);
        }

        if (best_diff == 1e18) best_diff = 0;

        if (parity) {
            return make_pair(sum, sum - best_diff + A[node]);
        } else {
            return make_pair(sum - best_diff, sum + A[node]);
        }
    };

    auto [odd, even] = dfs(0, -1);
    cout << max(odd, even) << '\n';
}