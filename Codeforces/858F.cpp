#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<vector<int>> children(n), back_edges(n);
    vector<int> depth(n, -1), par(n, -1);
    vector<int> needs_merge(n, true);

    auto dfs = [&](auto &&dfs, int node, int d = 0) -> void {
        depth[node] = d;
        for (auto x: adj[node]) {
            if (depth[x] == -1) {
                children[node].push_back(x);
                par[x] = node;
                dfs(dfs, x, d + 1);
            } else if (depth[x] < d - 1) {
                back_edges[node].push_back(x);
            }
        }
    };

    vector<array<int, 3>> episodes;

    auto process = [&](int node) {
        while (!children[node].empty()) {
            int child = children[node].back();
            children[node].pop_back();

            if (needs_merge[child]) {
                while (!children[node].empty() && !needs_merge[children[node].back()])
                    children[node].pop_back();

                if (!children[node].empty()) {
                    episodes.push_back({child, node, children[node].back()});
                    children[node].pop_back();
                } else if (back_edges[node].size() & 1) {
                    episodes.push_back({child, node, back_edges[node].back()});
                    back_edges[node].pop_back();
                } else if (par[node] != -1) {
                    episodes.push_back({child, node, par[node]});
                    needs_merge[node] = false;
                }
            }
        }

        if (back_edges[node].size() & 1) {
            episodes.push_back({par[node], node, back_edges[node].back()});
            back_edges[node].pop_back();
            needs_merge[node] = false;
        }

        for (int i = 0; i < back_edges[node].size(); i += 2) {
            episodes.push_back({back_edges[node][i], node, back_edges[node][i + 1]});
        }

    };

    for (int i = 0; i < n; i++)
        if (depth[i] == -1)
            dfs(dfs, i);

    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 0);
    sort(nodes.begin(), nodes.end(), [&](int i, int j) { return depth[i] > depth[j]; });

    for (auto i: nodes)
        process(i);

    cout << episodes.size() << '\n';
    for (auto [x, y, z]: episodes) {
        cout << x + 1 << ' ' << y + 1 << ' ' << z + 1 << '\n';
    }
}