#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    int n, m; cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    vector<vector<int>> adj(n);
 
    for (auto &[a, b, c]: edges) {
        cin >> a >> b >> c;
        a--, b--;

        adj[a].push_back(b);
    }
 
    vector<long long> dst(n, -1e18);
    dst[0] = 0;
 
    for (int i = 1; i < n; i++) {
        vector<long long> new_dst = dst;
        for (auto [a, b, c]: edges) {
            new_dst[b] = max(new_dst[b], dst[a] + c);
        }
        dst = new_dst;
    }
 
    vector<bool> visited(n);
    queue<int> q;
    for (auto [a, b, c]: edges) {
        if (dst[b] > -1e15 && dst[b] < dst[a] + c) {
            q.push(b);
        }
    }
 
    while (!q.empty()) {
        int node = q.front(); q.pop();
        if (visited[node]) continue;
        visited[node] = true;

        for (auto x: adj[node]) q.push(x);
    }

    if (visited[n - 1]) cout << -1 << '\n';
    else cout << dst[n - 1] << '\n';
}