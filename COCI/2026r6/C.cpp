#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    auto idx = [&](int i, int j) { return i * m + j; };
    int source = n * m, sink = n * m + 1;

    vector<set<int>> adj(n * m + 2);
    int nodes = 0;
    int models = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '2') models++;
            if (grid[i][j] == '1' || grid[i][j] == '2') continue;
            if (i > 0 && grid[i - 1][j] == '2') continue;
            if (i < n - 1 && grid[i + 1][j] == '2') continue;
            if (j > 0 && grid[i][j - 1] == '2') continue;
            if (j < m - 1 && grid[i][j + 1] == '2') continue;
            if ((i + j) % 2) {
                adj[idx(i, j)].insert(sink);
            } else {
                adj[source].insert(idx(i, j));

                if (i > 0) adj[idx(i, j)].insert(idx(i - 1, j));
                if (i < n - 1) adj[idx(i, j)].insert(idx(i + 1, j));
                if (j > 0) adj[idx(i, j)].insert(idx(i, j - 1));
                if (j < m - 1) adj[idx(i, j)].insert(idx(i, j + 1));
            }
            nodes++;
        }
    }

    vector<int> path;
    vector<bool> vis(n * m + 2);
    auto dfs = [&](auto &&dfs, int node) -> bool {
        path.push_back(node);
        vis[node] = true;
        if (node == sink) return true;

        for (auto x: adj[node]) {
            if (vis[x]) continue;
            if (dfs(dfs, x)) return true;
        }

        path.pop_back();
        return false;
    };
    
    int flow = 0;
    while ((path.clear(), vis.assign(n * m + 2, false), dfs(dfs, source))) {
        for (int i = 0; i < path.size() - 1; i++) {
            adj[path[i]].erase(path[i + 1]);
            adj[path[i + 1]].insert(path[i]);
        }
        flow++;
    }

    cout << nodes - flow + models << '\n';
}
