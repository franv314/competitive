#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        u--, v--;
    }

    vector<vector<int>> adj(n);
    for (auto &[u, v]: edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);;
    }

    multiset<int, greater<int>> degs;
    degs.insert(0);
    for (auto d: adj)
        degs.insert(d.size());
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        degs.erase(degs.find(adj[i].size()));
        for (auto d: adj[i])
            degs.erase(degs.find(adj[d].size()));
        
        ans = max(ans, (int)adj[i].size() + *degs.begin() - 1);

        degs.insert(adj[i].size());
        for (auto d: adj[i])
            degs.insert(adj[d].size());
    }

    for (auto [u, v]: edges)
        ans = max(ans, (int)adj[u].size() + (int)adj[v].size() - 2);

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
