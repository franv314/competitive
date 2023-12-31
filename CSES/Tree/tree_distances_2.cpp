#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<long long> sizes(n);
    vector<long long> ans(n);
    long long curr = 0;

    function<int(int, int, int)> dfs_1 = [&](int node, int par, int d) {
        curr += d;
        sizes[node] = 1;

        for (auto c: adj[node]) {
            if (c == par) continue;
            sizes[node] += dfs_1(c, node, d + 1);
        }

        return sizes[node];
    };

    function<void(int, int)> dfs_2 = [&](int node, int par) {
        if (par != -1) {
            curr += n - sizes[node] - sizes[node];
        }

        ans[node] = curr;
        for (auto c: adj[node]) {
            if (c == par) continue;
            dfs_2(c, node);
        }

        if (par != -1) {
            curr -= n - sizes[node] - sizes[node];
        }
    };

    dfs_1(0, -1, 0);
    dfs_2(0, -1);

    for (auto x: ans) cout << x << ' ';
}