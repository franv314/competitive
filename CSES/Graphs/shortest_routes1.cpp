#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
 
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
    }
 
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > q;
 
    vector<long long> D(n, 1e18);
    vector<bool> visited(n, false);
 
    D[0] = 0;
    q.push({0, 0});
 
    while (!q.empty()) {
        int x = q.top().second; q.pop();
        if (visited[x]) continue;
        visited[x] = true;
 
        for (auto [y, w]: adj[x]) {
            if (D[y] > D[x] + w) {
                D[y] = D[x] + w;
                q.push({D[y], y});
            }
        }
    }
 
    for (int i = 0; i < n; i++) cout << D[i] << " ";
    cout << "\n";
}