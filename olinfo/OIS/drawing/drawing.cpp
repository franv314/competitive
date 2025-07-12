#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> arr;

    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }

    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (arr[u] > arr[v]) swap(u, v);
        arr[u] += arr[v];
        arr[v] = u;

        return true;
    }

    DSU(int size) : arr(size, -1) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, e; cin >> n >> m >> e;

    vector<pair<int, int>> edges(e);
    vector<vector<int>> adj[2];
    adj[0].resize(n), adj[1].resize(m);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        adj[0][u].push_back(v);
        adj[1][v].push_back(u);
    }

    DSU dsu(n + m);
    for (auto [u, v]: edges)
        if (!dsu.join(u, n + v))
            return cout << "-1\n", 0;
    
    for (auto &cadj: adj[0]) {
        sort(cadj.begin(), cadj.end(), [&](int u, int v) { return adj[1][u].size() < adj[1][v].size(); });
        
        if (cadj.size() > 2 && adj[1][cadj[cadj.size() - 3]].size() != 1)
            return cout << "-1\n", 0;    
    }
    for (auto &cadj: adj[1]) {
        sort(cadj.begin(), cadj.end(), [&](int u, int v) { return adj[0][u].size() < adj[0][v].size(); });

        if (cadj.size() > 2 && adj[0][cadj[cadj.size() - 3]].size() != 1)
            return cout << "-1\n", 0;  
    }

    vector<bool> vis[2];
    vis[0].resize(n), vis[1].resize(m);
    vector<int> row[2];

    for (int sside: {0, 1}) {
        for (int i = 0; i < (sside ? m : n); i++) {
            if (vis[sside][i] || adj[sside][i].size() > 1) continue;
            if (adj[sside][i].size() > 0 && adj[sside ^ 1][adj[sside][i][0]].size() > 1 && adj[sside][adj[sside ^ 1][adj[sside][i][0]][adj[sside ^ 1][adj[sside][i][0]].size() - 2]].size() > 1) continue;
            
            int curr = i, side = sside;
            for (;;) {
                row[side].push_back(curr);
                vis[side][curr] = true;

                for (int j = 0; j < adj[side][curr].size() && adj[side ^ 1][adj[side][curr][j]].size() == 1; j++) {
                    if (vis[side ^ 1][adj[side][curr][j]]) continue;
                    row[side ^ 1].push_back(adj[side][curr][j]);
                    vis[side ^ 1][adj[side][curr][j]] = true;
                }

                if (adj[side][curr].size() > 0 && adj[side ^ 1][adj[side][curr][adj[side][curr].size() - 1]].size() >= 2 && !vis[side ^ 1][adj[side][curr][adj[side][curr].size() - 1]]) {
                    curr = adj[side][curr][adj[side][curr].size() - 1];
                    side ^= 1;
                } else if (adj[side][curr].size() > 1 && adj[side ^ 1][adj[side][curr][adj[side][curr].size() - 2]].size() >= 2 && !vis[side ^ 1][adj[side][curr][adj[side][curr].size() - 2]]) {
                    curr = adj[side][curr][adj[side][curr].size() - 2];
                    side ^= 1;
                } else {
                    break;
                }
            }
        }
    }

    for (auto x: row[0]) cout << x << " "; cout << "\n";
    for (auto x: row[1]) cout << x << " "; cout << "\n";
}
