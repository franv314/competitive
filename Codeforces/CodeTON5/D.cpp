#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, y; cin >> u >> v >> y;
        adj[u].emplace_back(v, y);
        adj[v].emplace_back(u, y);
    }
    
    vector<long long> dist_from_1(n + 1, 1e17);
    vector<long long> dist_from_n(n + 1, 1e17);
    {
        vector<bool> visited(n + 1);
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > q;
        
        dist_from_1[1] = 0;
        q.push({0, 1});
        while (!q.empty()) {
            auto [dst, node] = q.top(); q.pop();
            if (visited[node]) continue;
            visited[node] = true;
            
            for (auto [u, w]: adj[node]) {
                if (dist_from_1[u] > dst + w) {
                    dist_from_1[u] = dst + w;
                    q.push({dist_from_1[u], u});
                }
            }
        }
    }
    {
        vector<bool> visited(n + 1);
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > q;
        
        dist_from_n[n] = 0;
        q.push({0, n});
        while (!q.empty()) {
            auto [dst, node] = q.top(); q.pop();
            if (visited[node]) continue;
            visited[node] = true;
            
            for (auto [u, w]: adj[node]) {
                if (dist_from_n[u] > dst + w) {
                    dist_from_n[u] = dst + w;
                    q.push({dist_from_n[u], u});
                }
            }
        }
    }
    long long max_t = 1e18;
    for (int i = 1; i <= n; i++) {
        max_t = min(max_t, dist_from_1[i] + dist_from_n[i]);
    }
    
    if (max_t >= 1e17) {
        cout << "inf\n";
        return; 
    }
    
    vector<pair<long long, int>> times;
    for (int i = 1; i <= n; i++) {
        times.emplace_back(max_t - dist_from_1[i], i);
    }
    sort(times.begin(), times.end());

    vector<bool> current(n + 1, true);
    
    int diff = 0, old = 0;
    for (auto [t, i]: times) {
        if (t != old && t > 0) {
            old = t;
            diff++;
        }
    }
    
    long long time = 0;
    cout << max_t << ' ' << diff << '\n';
    for (auto [t, i]: times) {
        if (time >= t) {
            current[i] = false;
            continue;
        }
        int this_t = t - time;
        for (int i = 1; i <= n; i++) cout << current[i];
        cout << " " << this_t <<'\n';
        time = t;
        current[i] = false;
    }
}

int main() {
    solve();
}