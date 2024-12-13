#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    
    vector<vector<int>> adj_1(n), adj_2(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj_1[u - 1].push_back(v - 1);
        adj_1[v - 1].push_back(u - 1);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj_2[u - 1].push_back(v - 1);
        adj_2[v - 1].push_back(u - 1);
    }

    map<vector<int>, int> id;

    auto dfs = [&](auto &&dfs, const vector<vector<int>> &adj, int node, int par = -1) -> int {
        vector<int> children;
        for (auto x: adj[node])
            if (x != par)
                children.emplace_back(dfs(dfs, adj, x, node));
        
        sort(children.begin(), children.end());
        
        if (!id.count(children))
            id[children] = id.size();
        return id[children];
    };

    cout << (dfs(dfs, adj_1, 0) == dfs(dfs, adj_2, 0) ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}