#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a, b; cin >> n >> a >> b;
    a--, b--;
    vector<vector<int>> adj(n);

    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n);
    deque<int> st;
    function<bool(int, int)> dfs = [&](int node, int par) {
        st.push_back(node);
        visited[node] = true;
        for (auto x: adj[node]) {
            if (x == par) continue;
            if (visited[x]) {
                st.push_back(x);
                return true;
            }
            if (dfs(x, node)) return true;;
        }
        st.pop_back();
        return false;
    };

    dfs(0, -1);

    while (st.front() != st.back()) {
        st.pop_front();
    }

    if (st.size() < 3) {
        return void(cout << "NO\n");
    }

    vector<bool> cycle(n);
    for (auto x: st) {
        cycle[x] = true;
    }

    function<pair<int, int>(int, int)> dfs2 = [&](int node, int par) -> pair<int, int> {
        if (cycle[node]) return {node, 0};
        for (auto x: adj[node]) {
            if (x == par) continue;
            auto [n, d] = dfs2(x, node);
            if (d < 1e9) return {n, d + 1};
        }
        return {1e9, 1e9};
    };

    auto [tg, ds] = dfs2(b, -1);

    vector<int> dst(n);
    vector<bool> vis(n);
    queue<pair<int, int>> q;
    q.emplace(a, 0);

    while (!q.empty()) {
        auto [n, d] = q.front(); q.pop();
        if (vis[n]) continue;
        dst[n] = d;
        vis[n] = true;
        for (auto x: adj[n]) {
            q.emplace(x, d + 1);
        }
    }

    if (dst[tg] > ds) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}