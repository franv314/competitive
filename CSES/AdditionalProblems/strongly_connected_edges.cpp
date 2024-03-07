#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> depth(n, -2);
    vector<pair<int, int>> edges;

    function<int(int, int)> dfs = [&](int node, int d) -> int {
        depth[node] = d;
        int min_d = 1e9;
        for (auto x: adj[node]) {
            if (depth[x] == d - 1) continue;

            if (depth[x] == -2) {
                min_d = min(min_d, dfs(x, d + 1));
                edges.emplace_back(node, x);
            } else if (depth[x] < d) {
                min_d = min(min_d, depth[x]);
                edges.emplace_back(node, x);
            }
        }

        if (min_d >= d && node != 0) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }

        return min_d;
    };

    dfs(0, 0);

    if (any_of(depth.begin(), depth.end(), [](int x) { return x == -2; })) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (auto [u, v]: edges) {
        cout << u + 1 << ' ' << v + 1 << '\n';
    }
}