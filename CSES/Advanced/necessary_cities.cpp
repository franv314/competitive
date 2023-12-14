#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'001

bitset<MAXN> visited;
int depth[MAXN], hbe[MAXN];
vector<int> adj[MAXN];
vector<int> children[MAXN];

vector<int> ans;

int dfs(int node, int par = 0, int d = 0) {
    visited.set(node);
    depth[node] = d;
    hbe[node] = INT_MAX;
    int mi_sub = INT_MIN;
    for (auto n: adj[node]) {
        if (visited[n]) {
            if (n != par) hbe[node] = min(hbe[node], depth[n]);
        } else {
            int x = dfs(n, node, d + 1);
            hbe[node] = min(hbe[node], x);
            mi_sub = max(mi_sub, x);
            children[node].push_back(n);
        }
    }
    if (node == 1) {
        if (children[node].size() > 1) ans.push_back(node);
    } else if (mi_sub >= d) ans.push_back(node);
    return hbe[node];
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);
    cout << ans.size() << "\n";
    for (auto x: ans) cout << x << " ";
}