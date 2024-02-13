#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, K; cin >> N >> K;
    vector<int> T(N);
    for (auto &x: T) {
        cin >> x;
        x--;
    }

    int M; cin >> M;
    vector<vector<int>> dir_adj(K), inv_adj(K);
    vector<pair<int, int>> edges(M);
    vector<set<int>> adjset(K);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        u--, v--;
        adjset[u].insert(v);
        dir_adj[u].push_back(v);
        inv_adj[v].push_back(u);
    }

    vector<int> scc(K, -1);
    vector<bool> visited(K);
    vector<int> order;

    function<void(int)> dfs1 = [&](int node) {
        visited[node] = true;
        for (auto x: dir_adj[node]) {
            if (visited[x]) continue;
            dfs1(x);
        }
        order.push_back(node);
    };

    function<void(int, int)> dfs2 = [&](int node, int root) {
        scc[node] = root;
        for (auto x: inv_adj[node]) {
            if (scc[x] != -1) continue;
            dfs2(x, root);
        }
    };

    vector<int> scc_list;

    for (int i = 0; i < K; i++) {
        if (!visited[i]) dfs1(i);
    }
    reverse(order.begin(), order.end());
    for (auto i: order) {
        if (scc[i] == -1) {
            dfs2(i, i);
            scc_list.push_back(i);
        }
    }

    vector<vector<int>> scc_adj(K);
    vector<int> indeg(K);
    for (auto [u, v]: edges) {
        if (scc[u] == scc[v]) continue;
        scc_adj[scc[u]].push_back(scc[v]);
        indeg[scc[v]]++;
    }

    queue<int> q;
    for (auto i: scc_list) {
        if (indeg[i] == 0) q.push(i);
    }

    vector<int> topo_order;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        topo_order.push_back(x);
        for (auto y: scc_adj[x]) {
            if (--indeg[y] == 0) {
                q.push(y);
            }
        }
    }

    vector<int> topo_sort_pos(K, -1);
    for (int i = 0; i < topo_order.size(); i++) {
        topo_sort_pos[topo_order[i]] = i;
    }

    function<bool(int, int)> find_path = [&](int curr, int target) {
        if (curr == target) return true;
        if (topo_sort_pos[curr] > topo_sort_pos[target]) return false;

        for (auto x: scc_adj[curr]) {
            if (topo_sort_pos[x] > topo_sort_pos[target]) continue;
            if (find_path(x, target)) return true;
        }

        return false;
    };

    int points = 2;

    for (int i = 1; i < N; i++) {
        if (adjset[T[i - 1]].count(T[i])) {
            points += 2;
            continue;
        }

        if (scc[T[i - 1]] == scc[T[i]]) {
            points += 1;
            continue;
        }

        if (find_path(scc[T[i - 1]], scc[T[i]])) {
            points += 1;
            continue;
        }

        break;
    }

    cout << points << '\n';
}