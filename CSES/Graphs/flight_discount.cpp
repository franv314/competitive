#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[a].emplace_back(b, c);
    }

    vector<array<bool, 2>> visited(n, {false, false});
    vector<array<long long, 2>> dst(n, {(long long)1e18, (long long)1e18});
    priority_queue<
        tuple<long long, int, bool>,
        vector<tuple<long long, int, bool>>,
        greater<tuple<long long, int, bool>>
    > q;

    q.emplace(dst[0][0] = 0, 0, false);

    while (!q.empty()) {
        auto [d, node, used] = q.top(); q.pop();
        if (visited[node][used]) continue;
        visited[node][used] = true;

        for (auto [x, w]: adj[node]) {
            if (!used && d + w < dst[x][0]) {
                q.emplace(dst[x][0] = d + w, x, false);
            }
            if (!used && d + w / 2 < dst[x][1]) {
                q.emplace(dst[x][1] = d + w / 2, x, true);
            }
            if (used && d + w < dst[x][1]) {
                q.emplace(dst[x][1] = d + w, x, true);
            }
        }
    }

    cout << dst[n - 1][1] << '\n';
}