#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
        adj[v - 1].emplace_back(u - 1, w);
    }

    vector<int> s(n);
    for (auto &x: s) cin >> x;

    priority_queue<
        tuple<long long, int, int>,
        vector<tuple<long long, int, int>>,
        greater<tuple<long long, int, int>>
    > q;
    vector<vector<long long>> dst(n, vector<long long>(1001, 1e18));
    vector<vector<bool>> visited(n, vector<bool>(1001));

    q.emplace(dst[0][s[0]] = 0, 0, s[0]);
    while (!q.empty()) {
        auto [d, n, b] = q.top(); q.pop();
        
        if (b != 1000 && dst[n][b + 1] > d) {
            q.emplace(dst[n][b + 1] = d, n, b + 1);
        }

        int bn = min(b, s[n]);
        for (auto [nb, w]: adj[n]) {
            if (dst[nb][bn] > d + (long long)w * bn) {
                q.emplace(dst[nb][bn] = d + (long long)w * bn, nb, bn);
            }
        }
    }

    cout << dst[n - 1][1000] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}