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

    vector<multiset<int>> vals(n);
    vector<int> ans(n);

    function<int(int, int)> dfs_1 = [&](int node, int par) {
        vals[node].insert(0);
        for (auto c: adj[node]) {
            if (c == par) continue;
            vals[node].insert(dfs_1(c, node));
        }
        return 1 + *vals[node].rbegin();
    };

    function<void(int, int)> dfs_2 = [&](int node, int par) {
        int added, removed;
        if (par != -1) {
            vals[par].erase(vals[par].find(removed = 1 + *vals[node].rbegin()));
            vals[node].insert(added = 1 + *vals[par].rbegin());
        }

        ans[node] = *vals[node].rbegin();

        for (auto c: adj[node]) {
            if (c == par) continue;
            dfs_2(c, node);
        }

        if (par != -1) {
            vals[par].insert(removed);
            vals[node].erase(vals[node].find(added));
        }
    };

    dfs_1(0, -1);
    dfs_2(0, -1);

    for (auto x: ans) cout << x << ' ';
}