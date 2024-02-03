#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    deque<int> path;
    vector<bool> visited(N);

    function<bool(int, int)> dfs = [&](int node, int par) {
        path.push_back(node);
        visited[node] = true;

        for (auto x: adj[node]) {
            if (x == par) continue;
            if (visited[x]) {
                path.push_back(x);
                return true;
            }

            if (dfs(x, node)) return true;
        }

        path.pop_back();
        return false;
    };

    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;

        if (dfs(i, -1)) {
            while (path[0] != path.back()) path.pop_front();
            cout << path.size() << '\n';
            for (auto x: path) cout << x + 1 << ' '; cout << '\n';

            return 0;
        }
    }

    cout << "IMPOSSIBLE";
}