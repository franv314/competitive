#include <bits/stdc++.h>
using namespace std;

#define MAXN 50'000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, q; cin >> n >> m >> q;

    vector<vector<int>> dir(n), inv(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        dir[a].push_back(b);
        inv[b].push_back(a);
    }

    vector<bool> visited(n);
    vector<int> scc(n, -1);
    vector<int> order;

    function<void(int)> dfs1 = [&](int node) {
        visited[node] = true;
        for (auto x: dir[node])
            if (!visited[x])
                dfs1(x);
        order.push_back(node);
    };

    function<void(int, int)> dfs2 = [&](int node, int root) {
        scc[node] = root;
        for (auto x: inv[node])
            if (scc[x] == -1)
                dfs2(x, root);
    };

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs1(i);
    
    reverse(order.begin(), order.end());
    for (auto i: order)
        if (scc[i] == -1)
            dfs2(i, i);

    vector<vector<int>> scc_adj(n);
    for (int i = 0; i < n; i++) {
        for (auto x: dir[i])
            scc_adj[scc[i]].push_back(scc[x]);
    }

    vector<bitset<MAXN>> dp(n);

    function<void(int)> rec = [&](int node) {
        if (dp[node][node]) return;
        dp[node].set(node);

        for (auto x: scc_adj[node]) {
            rec(x);
            dp[node] |= dp[x];
        }
    };

    for (int i = 0; i < n; i++)
        rec(i);

    while (q--) {
        int a, b; cin >> a >> b;
        a--, b--;

        cout << (scc[a] == scc[b] || dp[scc[a]][scc[b]] ? "YES\n" : "NO\n");
    }
}