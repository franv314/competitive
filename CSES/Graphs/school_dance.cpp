#include <bits/stdc++.h>
using namespace std;

bitset<1002> visited;
vector<int> path;
unordered_set<int> adj[1002];

bool dfs(int node) {
    visited.set(node);
    path.push_back(node);
    if (path.back() == 1001) return true;

    for (auto d: adj[node]) {
        if (visited[d]) continue;
        if (dfs(d)) return true;
    }
    path.pop_back();
    return false;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        adj[a].insert(500 + b);
    }

    for (int i = 1; i <= n; i++) {
        adj[0].insert(i);
    }
    for (int i = 1; i <= m; i++) {
        adj[500 + i].insert(1001);
    }

    int match = 0;
    for (;;) {
        visited.reset();
        path.clear();
        if (!dfs(0)) break;

        for (int i = 0; i < path.size() - 1; i++) {
            adj[path[i]].erase(path[i + 1]);
            adj[path[i + 1]].insert(path[i]);
        }
        match++;
    }

    cout << match << "\n";
    for (int i = 501; i <= 500 + m; i++) {
        for (auto x: adj[i]) {
            if (x > 0 && x <= 500) {
                cout << x << " " << i - 500 << "\n";
            }
        }
    }
}