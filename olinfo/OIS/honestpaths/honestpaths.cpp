#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> adj(N);
    
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
        adj[v - 1].emplace_back(u - 1, w);
    }

    vector<i64> dst(N, 1e18);
    vector<bool> vis(N);
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> q;

    q.emplace(dst[N - 1] = 0, N - 1);
    while (!q.empty()) {
        auto [d, x] = q.top(); q.pop();
        if (vis[x]) continue;
        vis[x] = true;

        for (auto [y, w]: adj[x])
            if (d + w < dst[y])
                q.emplace(dst[y] = d + w, y);
    }

    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 0);
    sort(nodes.begin(), nodes.end(), [&](int u, int v) { return dst[u] > dst[v]; });

    vector<pair<i64, int>> dp(N, make_pair(-1e18, -1));

    for (auto x: nodes) {
        dp[x] = {0, x};
        for (auto [y, w]: adj[x]) {
            if (dst[y] > dst[x]) {
                dp[x] = max(dp[x], {dp[y].first + w, y});
            }
        }
    }

    vector<int> path;
    for (int curr = N - 1; ; curr = dp[curr].second) {
        path.push_back(curr);
        if (dp[curr].second == curr) break;
    }
    reverse(path.begin(), path.end());

    cout << dp[N - 1].first << ' ' << path.size() << '\n';
    for (auto x: path) cout << x + 1 << ' '; cout << '\n';
}
