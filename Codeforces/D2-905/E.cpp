#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, t; cin >> n >> t;
    vector<vector<pair<int, int>>> adj_cell(n);
    vector<vector<pair<int, int>>> pot(t);
    for (int i = 0; i < t; i++) {
        int m; cin >> m;
        for (int j = 0; j < m; j++) {
            int u, v; cin >> u >> v;
            u--, v--;

            adj_cell[u].emplace_back(v, i);
            adj_cell[v].emplace_back(u, i);
        }
    }

    int k; cin >> k;
    vector<int> a(k);
    for (auto &x: a) cin >> x;

    vector<bool> visited(n);
    visited[0] = true;

    for (auto [n, nt]: adj_cell[0]) {
        pot[nt].emplace_back(0, n);
    }
    adj_cell[0].clear();

    for (int i = 0; i < k; i++) {
        int curr_t = a[i] - 1;

        vector<pair<int, int>> ed = pot[curr_t];
        pot[curr_t].clear();

        for (auto [x, y]: ed) {
            if (!visited[y]) {
                visited[y] = true;
                for (auto [n, nt]: adj_cell[y]) {
                    pot[nt].emplace_back(y, n);
                }
                adj_cell[y].clear();
            }
        }

        if (visited[n - 1]) return void(cout << i + 1 << '\n');
    }
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}