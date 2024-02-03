#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;

    vector<vector<int>> dir(N), inv(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        dir[u - 1].push_back(v - 1);
        inv[v - 1].push_back(u - 1);
    }

    vector<bool> visited(N);
    vector<int> scc(N, -1);
    vector<int> order;

    function<void(int)> dfs1 = [&](int node) {
        visited[node] = true;
        for (auto x: dir[node]) {
            if (!visited[x]) {
                dfs1(x);
            }
        }
        order.push_back(node);
    };

    function<void(int, int)> dfs2 = [&](int node, int root) {
        scc[node] = root;
        for (auto x: inv[node])  {
            if (scc[x] == -1) {
                dfs2(x, root);
            }
        }
    };

    for (int i = 0; i < N; i++) {
        if (!visited[i]) dfs1(i);
    }
    reverse(order.begin(), order.end());
    for (auto i: order) {
        if (scc[i] == -1) dfs2(i, i);
    }

    deque<int> path;
    vector<bool> visited2(N);
    function<bool(int, int, int)> get_path = [&](int node, int end, int root) {
        path.push_back(node);
        visited2[node] = true;

        if (node == end) return true;

        for (auto x: dir[node]) {
            if (visited2[x] || scc[x] != root) continue;
            if (get_path(x, end, root)) return true;
        }

        path.pop_back();
        return false;
    };

    vector<vector<int>> comp(N);
    for (int i = 0; i < N; i++) comp[scc[i]].push_back(i);

    for (int i = 0; i < N; i++) {
        if (comp[i].size() < 2) continue;

        for (auto u: comp[i]) {
            for (auto v: dir[u]) {
                if (scc[v] != scc[u]) continue;
                assert(get_path(v, u, i));

                cout << path.size() + 1 << '\n';
                cout << u + 1 << ' ';
                for (auto x: path) cout << x + 1 << ' ';
                cout << '\n';
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}