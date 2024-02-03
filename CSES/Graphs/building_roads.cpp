#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }

    vector<bool> visited(n);
    vector<int> cc;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        cc.push_back(i);

        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int node = q.front(); q.pop();
            if (visited[node]) continue;
            visited[node] = true;

            for (auto x: adj[node]) q.push(x);
        }
    }

    cout << cc.size() - 1 << '\n';
    for (int i = 0; i < cc.size() - 1; i++) cout << cc[i] + 1 << ' ' << cc[i + 1] + 1 << '\n';
}