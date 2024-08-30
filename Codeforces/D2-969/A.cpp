#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    string s; cin >> s;

    int leaf_0 = 0, leaf_1 = 0, leaf_u = 0, nl = 0;
    auto dfs = [&](auto &&dfs, int node, int par = -1) -> void {
        bool has_children = false;
        for (auto x: adj[node]) {
            if (x == par) continue;
            has_children = true;
            dfs(dfs, x, node);
        }

        if (!has_children) {
            switch (s[node]) {
            case '0': leaf_0++; break;
            case '1': leaf_1++; break;
            case '?': leaf_u++; break;
            }
        } else if (par != -1) nl += s[node] == '?';
    };

    dfs(dfs, 0);

    if (s[0] == '0') {
        cout << leaf_1 + (leaf_u + 1) / 2 << '\n';
        return;
    }
    if (s[0] == '1') {
        cout << leaf_0 + (leaf_u + 1) / 2 << '\n';
        return;
    }

    if (leaf_0 > leaf_1) {
        if (nl % 2 == 0) cout << leaf_0 + leaf_u / 2 << '\n';
        else cout << max(leaf_1 + (leaf_u + 1) / 2, leaf_0 + leaf_u / 2) << '\n';
    } else {
        if (nl % 2 == 0) cout << leaf_1 + leaf_u / 2 << '\n';
        else cout << max(leaf_0 + (leaf_u + 1) / 2, leaf_1 + leaf_u / 2) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}