#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

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

    int ans = 1;
    vector<bool> visited(n);

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        int nodes = 0, edges = 0;
        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int x = q.front(); q.pop();
            if (visited[x]) continue;
            
            visited[x] = true;
            nodes++;

            for (auto y: adj[x]) {
                q.push(y);
                edges++;
            }
        }

        edges /= 2;
        for (int j = 0; j < edges - nodes + 1; j++) ans = (2 * ans) % MOD;
    }

    cout << ans << '\n';
}