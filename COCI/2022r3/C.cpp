#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edges(m);
    vector<vector<pair<int, int>>> adj(n);
    
    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--, edges[i][1]--;
        adj[edges[i][0]].emplace_back(edges[i][1], edges[i][2]);
        adj[edges[i][1]].emplace_back(edges[i][0], edges[i][2]);
    }
    
    auto dijkstra = [&](int start) -> vector<array<int64_t, 2>> {
        vector<array<int64_t, 2>> dst(n, {(int64_t)1e18, (int64_t)1e18});
        vector<int> visited(n);
        priority_queue<
            pair<int64_t, int>,
            vector<pair<int64_t, int>>,
            greater<pair<int64_t, int>>
        > q;
        
        dst[start][0] = 0;
        q.emplace(0, start);
        
        while (!q.empty()) {
            auto [d, p] = q.top(); q.pop();
            if (visited[p] == 2 || (visited[p] == 1 && d == dst[p][0])) continue;
            
            dst[p][visited[p]] = d;
            visited[p]++;
            
            for (auto [neighbour, weight]: adj[p]) {
                q.emplace(d + weight, neighbour);
            }
        }
        
        return dst;
    };
    
    auto dst_start = dijkstra(0);
    auto dst_end = dijkstra(n - 1);
    int64_t opt = dst_start[n - 1][0];
    int64_t sub = dst_start[n - 1][1];
    
    if (sub != opt + 1) {
        cout << "0\n\n";
        return;
    }
    
    vector<vector<pair<int, int>>> adj_opt(n), adj_sub(n);
    for (int i = 0; i < m; i++) {
        auto [a, b, w] = edges[i];
        int64_t fst = w + min(dst_start[a][0] + dst_end[b][0], dst_start[b][0] + dst_end[a][0]);
        int64_t snd = w + min({
            dst_start[a][0] + dst_end[b][1],
            dst_start[b][0] + dst_end[a][1],
            dst_start[a][1] + dst_end[b][0],
            dst_start[b][1] + dst_end[a][0],
        });
        
        if (fst == opt) {
            adj_opt[a].emplace_back(b, i);
            adj_opt[b].emplace_back(a, i);
        }
        
        if (fst == sub || snd == sub) {
            adj_sub[a].emplace_back(b, i);
            adj_sub[b].emplace_back(a, i);
        }
    }
    
    vector<int> depth(n);
    vector<int> bridge_opt, bridge_sub;
    function<int(int, int, int, vector<vector<pair<int, int>>>&, vector<int>&)> find_bridges =
        [&](int node, int d, int p, vector<vector<pair<int, int>>> &adj, vector<int> &ans) -> int 
    {
        depth[node] = d;
        int mi = INT_MAX;
        
        for (auto [c, idx]: adj[node]) {
            if (c == p) continue;
            if (depth[c] != -1) {
                mi = min(mi, depth[c]);
            } else {
                int c_mi = find_bridges(c, d + 1, node, adj, ans);
                mi = min(mi, c_mi);
                if (c_mi > d) {
                    ans.push_back(idx);
                }
            }
        }
        
        return mi;
    };
    
    fill(depth.begin(), depth.end(), -1);
    find_bridges(0, 0, -1, adj_opt, bridge_opt);
    
    fill(depth.begin(), depth.end(), -1);
    find_bridges(0, 0, -1, adj_sub, bridge_sub);
    
    vector<int> ans;
    sort(bridge_opt.begin(), bridge_opt.end());
    sort(bridge_sub.begin(), bridge_sub.end());
    set_difference(bridge_opt.begin(), bridge_opt.end(), bridge_sub.begin(), bridge_sub.end(), back_inserter(ans));
    
    cout << ans.size() << "\n";
    for (auto x: ans) {
        cout << x + 1 << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}