#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> adj(N);
    vector<bool> visited(N), used(M);

    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }

    function<int(int, int)> find_loop = [&](int node, int par) {
        if (visited[node]) return node;
        visited[node] = true;
        for (auto [c, _]: adj[node]) {
            if (c != par) {
                int res = find_loop(c, node);
                if (res != -1) return res;
            }
        }
        return -1;
    };

    function<void(int, int)> orient = [&](int node, int par) {
        visited[node] = true;
        for (auto [c, idx]: adj[node]) {
            if (used[idx]) continue;
            used[idx] = true;
            cout << node << " " << c << '\n';
            if (!visited[c]) orient(c, node);
        }
    };

    int root = find_loop(0, -1);
    fill(visited.begin(), visited.end(), false);
    orient(root, -1);
}