#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<pair<int, int>> edges(M);
    for (auto &[u, v]: edges) cin >> u >> v;

    sort(edges.begin(), edges.end(), [&](const pair<int, int> &a, const pair<int, int> &b) {
        return (a.second - a.first + N) % N < (b.second - b.first + N) % N;
    });

    vector<pair<int, int>> next(N);
    for (int i = 0; i < N; i++) {
        next[i] = {(i + 1) % N, -1};
    }

    vector<vector<array<int, 3>>> adj;

    for (auto [u, v]: edges) {
        adj.emplace_back();
        
        int curr = u;
        while (curr != v) {
            adj.back().push_back({next[curr].second, curr, next[curr].first});
            int nxt = next[curr].first;
            next[curr] = {-2, -2};
            curr = nxt;
        }

        next[u] = {v, adj.size() - 1};
    }
    {
        adj.emplace_back();
        int start = find_if(next.begin(), next.end(), [&](const pair<int, int> &a) {
            return a.second != -2;
        }) - next.begin();

        int curr = start;
        do {
            adj.back().push_back({next[curr].second, curr, next[curr].first});
        } while ((curr = next[curr].first) != start);
    }

    vector<pair<int, int>> data(adj.size() + 1);
    pair<int, int> *dp = data.data() + 1;

    auto dp_merge = [](const pair<int, int> &dp_a, const pair<int, int> &dp_b) {
        return make_pair(
            min(dp_a.first + dp_b.first, dp_a.second + dp_b.second),
            min(dp_a.first + dp_b.second, dp_a.second + dp_b.first)
        );
    };

    auto dfs = [&](auto &&dfs, int node) -> void {
        if (node == -1) return;

        dp[node] = {-1, -1};
        for (auto [ch, _, __]: adj[node]) {
            dfs(dfs, ch);

            if (dp[node].first == -1) {
                dp[node] = dp[ch];
            } else {
                dp[node] = dp_merge(dp[node], dp[ch]);
            }
        }

        dp[node].first++;
    };

    vector<bool> ans(N);

    auto accesspair = [&](pair<int, int> &p, int idx) -> int& {
        if (idx == 0) return p.first;
        return p.second;
    };

    auto dfs2 = [&](auto &&dfs2, int node, pair<int, int> edge, bool flip, int d = 0) -> void {
        if (node == -1) return;

        vector<pair<int, int>> prefix_dp;
        for (auto [ch, _, __]: adj[node]) {
            if (prefix_dp.empty()) prefix_dp.push_back(dp[ch]);
            else prefix_dp.push_back(dp_merge(prefix_dp.back(), dp[ch]));
        }

        bool suff_way = false;
        int suff_cost = !flip;

        for (int i = adj[node].size() - 1; i > 0; i--) {
            auto [ch, x, y] = adj[node][i];

            int merged_same = suff_cost + dp[ch].first + accesspair(prefix_dp[i - 1], flip ^ suff_way);
            int merged_diff = suff_cost + dp[ch].second + accesspair(prefix_dp[i - 1], (!flip) ^ suff_way);

            if (merged_same == accesspair(dp[node], flip)) {
                ans[x] = ans[y];
                dfs2(dfs2, ch, {x, y}, false);

                suff_cost += dp[ch].first;
            } else {
                assert(merged_diff == accesspair(dp[node], flip));
                ans[x] = !ans[y];
                dfs2(dfs2, ch, {x, y}, true);

                suff_way ^= true;
                suff_cost += dp[ch].second;
            }
        }

        {
            auto [ch, x, y] = adj[node][0];
            if (suff_way ^ flip) {
                ans[x] = !ans[y];
                dfs2(dfs2, ch, {x, y}, true);
            } else {
                ans[x] = ans[y];
                dfs2(dfs2, ch, {x, y}, false);
            }
        }
    };

    dp[-1] = {1, 0};
    dfs(dfs, adj.size() - 1);
    
    dfs2(dfs2, adj.size() - 1, {-1, -1}, false);

    cout << dp[adj.size() - 1].first - 1 << '\n';
    for (auto x: ans) cout << x << " "; cout << '\n';
}