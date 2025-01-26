#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> w(n);
    for (auto &x: w) cin >> x;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    int timer = 0;
    vector<int> tin(n), tout(n), depth(n);
    vector<vector<int>> lift(n);

    auto dfs = [&](auto &&dfs, int node, int par = -1, int d = 0) -> void {
        tin[node] = timer++;
        depth[node] = d;

        if (par != -1) {
            lift[node].push_back(par);
            for (int i = 0; lift[lift[node][i]].size() > i; i++)
                lift[node].push_back(lift[lift[node][i]][i]);
        }

        for (auto ch: adj[node]) {
            if (ch == par) continue;

            dfs(dfs, ch, node, d + 1);
        }

        tout[node] = timer;
    };

    auto lca = [&](int u, int v) {
        if (depth[u] > depth[v])
            swap(u, v);

        for (int i = lift[v].size() - 1; i >= 0; i--) {
            if (i < lift[v].size() && depth[lift[v][i]] >= depth[u]) {
                v = lift[v][i];
            }
        }

        if (u == v)
            return u;
        
        for (int i = lift[v].size() - 1; i >= 0; i--) {
            if (i < lift[v].size() && lift[v][i] != lift[u][i]) {
                v = lift[v][i];
                u = lift[u][i];
            }
        }

        return lift[u][0];
    };

    dfs(dfs, 0);

    map<int, vector<int>, greater<int>> mp;
    for (int i = 0; i < n; i++) {
        mp[w[i]].push_back(i);
    }

    auto lca2 = [&](vector<int> nodes) {
        int l = nodes[0];
        for (int i = 1; i < nodes.size(); i++)
            l = lca(l, nodes[i]);
        return l;
    };

    auto vec1 = mp.begin()->second;
    int l = lca2(vec1);
    mp.erase(mp.begin());

    for (auto [_, vec1]: mp) {
        for (auto x: vec1)
            if (tin[l] < tin[x] || tin[l] >= tout[x])
                return void(cout << x + 1 << '\n');

        l = lca(l, lca2(vec1));
    }

    cout << "0\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
