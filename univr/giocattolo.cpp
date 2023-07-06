#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> adj(n);
    vector<vector<int>> radj(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        swap(u, v);
        adj[v]++;
        radj[u].push_back(v);
    }

    set<pair<int, int>> nodes;
    for (int i = 0; i < n; i++) {
        nodes.insert({adj[i], i});
    }

    int ans = 0;
    while (nodes.size() && nodes.begin()->first == 0) {
        ans++;
        int node = nodes.begin()->second; nodes.erase(nodes.begin());
        for (auto n: radj[node]) {
            nodes.erase({adj[n], n});
            adj[n]--;
            nodes.insert({adj[n], n});
        }
        radj[node].clear();
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}