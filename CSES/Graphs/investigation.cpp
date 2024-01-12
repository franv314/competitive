#pragma GCC optimize("trapv")
#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[a].emplace_back(b, c);
    }

    vector<long long> dst(n, 1e18);
    vector<int> visited(n);
    vector<vector<int>> parents(n);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<>
    > q;

    q.emplace(dst[0] = 0, 0);
    while (!q.empty()) {
        auto [d, n] = q.top(); q.pop();
        if (visited[n]) continue;
        visited[n] = true;

        for (auto [x, w]: adj[n]) {
            if (d + w == dst[x]) {
                parents[x].push_back(n);
            } else if (d + w < dst[x]) {
                parents[x].clear();
                parents[x].push_back(n);

                q.emplace(dst[x] = d + w, x);
            }
        }
    }

    vector<optional<array<int, 3>>> dp(n);

    function<void(int)> rec = [&](int node) {
        if (node == 0) {
            dp[node] = {1, 0, 0};
            return;
        }

        dp[node] = {0, INT_MAX, INT_MIN};
        for (auto p: parents[node]) {
            if (!dp[p]) rec(p);
            (dp[node].value()[0] += dp[p].value()[0]) %= MOD;
            dp[node].value()[1] = min(dp[node].value()[1], dp[p].value()[1] + 1);
            dp[node].value()[2] = max(dp[node].value()[2], dp[p].value()[2] + 1);
        }
    };

    rec(n - 1);
    cout << dst[n - 1] << ' ' << dp[n - 1].value()[0] << ' ' << dp[n - 1].value()[1] << ' ' << dp[n - 1].value()[2] << '\n';
}