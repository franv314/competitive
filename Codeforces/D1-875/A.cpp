#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'001

vector<pair<int, int>> adj[MAXN];

int dfs(int node, int par = -1, int pos = -1) {
    int ris = 0;
    for (auto [c, p]: adj[node]) {
        if (c == par) continue;
        
        int r = dfs(c, node, p);
        if (p > pos) ris = max(ris, r);
        else ris = max(ris, r + 1);
    }
    return ris;
}

void solve() {
    int N; cin >> N;

    for (int i = 1; i <= N; i++) adj[i].clear();

    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    cout << 1 + dfs(1) << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}