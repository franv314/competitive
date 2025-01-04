#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> arr;

    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }

    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return false;
    
        if (arr[u] > arr[v])
            swap(u, v);
        
        arr[u] += arr[v];
        arr[v] = u;

        return true;
    }

    DSU(int size) : arr(size, -1) { }
};

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<array<int, 3>> edges;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({u - 1, v - 1, w});
        adj[u - 1].emplace_back(v - 1, w);
        adj[v - 1].emplace_back(u - 1, w);
    }

    sort(edges.begin(), edges.end(), [&](const auto &u, const auto &v) { return u[2] < v[2]; });
    vector<array<int, 3>> intedges;

    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        if (dsu.join(edges[i][0], edges[i][1]))
            intedges.push_back(edges[i]);
    }

    int z = intedges.size();

    vector<array<vector<int>, 2>> dst(z);
    for (int i = 0; i < z; i++) {
        for (int ext: {0, 1}) {
            vector<bool> visited(n);
            vector<int> &d = dst[i][ext];
            d.assign(n, 1e9);

            deque<pair<int, int>> q;
            q.emplace_back(intedges[i][ext], 0);
            d[intedges[i][ext]] = 0;

            while (!q.empty()) {
                auto [x, D] = q.front(); q.pop_front();
                if (visited[x]) continue;
                d[x] = D;
                visited[x] = true;

                for (auto [y, w]: adj[x]) {
                    if (x == intedges[i][0] && y == intedges[i][1]) continue;
                    if (x == intedges[i][1] && y == intedges[i][0]) continue;
                    
                    if (w > intedges[i][2]) {
                        q.emplace_back(y, d[x] + 1);
                    } else {
                        q.emplace_front(y, d[x]);
                    }
                }
            }
        }
    }

    while (q--) {
        int a, b, k; cin >> a >> b >> k;
        a--, b--;

        int ans = 1e9;
        for (int i = 0; i < z; i++) {
            int d = min(dst[i][0][a] + dst[i][1][b], dst[i][1][a] + dst[i][0][b]);
            if (d < k) {
                ans = min(ans, intedges[i][2]);
            }
        }
 
        cout << ans << ' ';
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}