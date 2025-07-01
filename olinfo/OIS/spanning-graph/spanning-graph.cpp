#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<pair<int, int>> edges(m);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        if (u > v) swap(u, v);
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n);
    vector<pair<int, int>> kept;

    auto rec = [&](auto &&rec, int node) -> bool {
        visited[node] = true;
        bool conn_to_par = true;

        for (auto x: adj[node]) {
            if (!visited[x] && rec(rec, x)) {
                conn_to_par ^= true;
                kept.emplace_back(min(x, node), max(x, node));
            }
        }

        return conn_to_par;
    };

    int ans = n;
    for (int i = 0; i < n; i++)
        if (!visited[i])
            ans -= rec(rec, i);

    int elim_no = m - kept.size();

    sort(edges.begin(), edges.end());
    sort(kept.begin(), kept.end());

    vector<pair<int, int>> elim(elim_no);
    set_difference(edges.begin(), edges.end(), kept.begin(), kept.end(), elim.begin());

    cout << ans << '\n' << elim_no << '\n';
    for (auto [u, v]: elim)
        cout << u + 1 << ' ' << v + 1 << '\n';
}
