#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'001

bitset<MAXN> visited;
int depth[MAXN], hbe[MAXN];
vector<int> adj[MAXN];
vector<int> children[MAXN];

int dfs(int node, int par = 0, int d = 0) {
    visited.set(node);
    depth[node] = d;
    hbe[node] = INT_MAX;
    for (auto n: adj[node]) {
        if (visited[n]) {
            if (n != par) hbe[node] = min(hbe[node], depth[n]);
        } else {
            hbe[node] = min(hbe[node], dfs(n, node, d + 1));
            children[node].push_back(n);
        }
    }
    return hbe[node];
}

vector<pair<int, int>> bridges;

void dfs2(int node) {
    for (auto child: children[node]) {
        if (hbe[child] > depth[node]) {
            bridges.push_back({node, child});
        }
        dfs2(child);
    }
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);
    dfs2(1);
    cout << bridges.size() << "\n";
    for (auto [u, v]: bridges) cout << u << " " << v << "\n";
}