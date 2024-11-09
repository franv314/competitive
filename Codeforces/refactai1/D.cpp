#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;

    vector<set<int>> adj(n);
    set<pair<int, int>, greater<>> nodedeg;

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].insert(v - 1);
        adj[v - 1].insert(u - 1);
    }

    for (int i = 0; i < n; i++) {
        nodedeg.emplace(adj[i].size(), i);
    }

    vector<array<int, 3>> moves;

    while (nodedeg.begin()->first > 1) {
        auto [_, node] = *nodedeg.begin(); nodedeg.erase(nodedeg.begin());

        int na = *adj[node].begin(); adj[node].erase(adj[node].begin());
        int nb = *adj[node].begin(); adj[node].erase(adj[node].begin());
        moves.push_back({node, na, nb});

        nodedeg.erase({adj[na].size(), na});
        nodedeg.erase({adj[nb].size(), nb});

        adj[na].erase(node);
        adj[nb].erase(node);

        if (adj[na].count(nb)) {
            adj[na].erase(nb);
            adj[nb].erase(na);
        } else {
            adj[na].insert(nb);
            adj[nb].insert(na);
        }

        nodedeg.emplace(adj[node].size(), node);
        nodedeg.emplace(adj[na].size(), na);
        nodedeg.emplace(adj[nb].size(), nb);
    }

    vector<vector<int>> cc;
    vector<bool> vis(n);
    int twonodecc = -1;

    for (int i = 0; i < n; i++) {
        if (vis[i])
            continue;

        assert(adj[i].size() <= 1);

        cc.emplace_back();

        cc.back().push_back(i);
        vis[i] = true;

        if (!adj[i].empty()) {
            twonodecc = cc.size() - 1;
            auto x = *adj[i].begin();
            vis[x] = true;
            cc.back().push_back(x);
        }
    }

    if (twonodecc != -1) {
        swap(cc[twonodecc], cc.back());

        if (cc.size() == 2) {
            moves.push_back({cc[cc.size() - 1][0], cc[cc.size() - 1][1], cc[cc.size() - 2][0]});
        } else {
            for (int i = 2; i < cc.size(); i++)
                moves.push_back({cc[i][0], cc[i - 1][0], cc[0][0]});

            moves.push_back({cc[cc.size() - 1][0], cc[cc.size() - 1][1], cc[cc.size() - 2][0]});
        }
    }

    cout << moves.size() << '\n';
    for (auto [x, y, z]: moves) {
        cout << x + 1 << " " << y + 1 << " " << z + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}