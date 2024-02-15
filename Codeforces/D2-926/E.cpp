#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> edges(n - 1);
    vector<vector<pair<int, int>>> adj(n);

    int z = 0;
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        u--, v--;
        adj[u].emplace_back(v, z);
        adj[v].emplace_back(u, z);
        z++;
    }

    int k; cin >> k;
    vector<pair<int, int>> paths(k);
    for (auto &[a, b]: paths) {
        cin >> a >> b;
        a--, b--;
    }

    vector<int> covers(n - 1);
    vector<int> path;

    auto dfs = [&](auto &&dfs, int node, int par, int target) -> bool {
        if (node == target) return true;
        for (auto [x, idx]: adj[node]) {
            if (x == par) continue;

            path.push_back(idx);
            if (dfs(dfs, x, node, target)) return true;
            path.pop_back();
        }
        return false;
    };

    for (int i = 0; i < k; i++) {
        auto [u, v] = paths[i];
        path.clear();
        dfs(dfs, u, -1, v);
        for (auto x: path) covers[x] |= (1 << i);
    }

    sort(covers.begin(), covers.end());
    covers.resize(unique(covers.begin(), covers.end()) - covers.begin());

    vector<bool> usable(covers.size(), true);
    for (int i = 0; i < covers.size(); i++) {
        for (int j = i + 1; j < covers.size(); j++) {
            if ((covers[i] & covers[j]) == covers[i]) {
                usable[i] = false;
                break;
            }
        }
    }

    vector<int> dp(1 << k, 1e9);
    dp[0] = 0;

    for (int j = 0; j < covers.size(); j++) {
        if (!usable[j]) continue;
        int cover = covers[j];
        for (int i = 0; i < (1 << k); i++) {
            dp[i | cover] = min(dp[i | cover], dp[i] + 1);
        }
    }

    cout << dp.back() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}