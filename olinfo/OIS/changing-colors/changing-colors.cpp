#include <bits/stdc++.h>
using namespace std;

constexpr int MAXB = 16;

int main() {
    int N; cin >> N;
    vector<pair<int, int>> edges(N - 1);
    vector<vector<int>> adj(N);
    for (auto &[u, v]: edges) {
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int x = 0;
    for (int b = 0; b < MAXB; b++) {
        cout << "? ";
        for (int i = 0; i < N - 1; i++)
            cout << ((i >> b) & 1) << ' ';
        cout << endl;

        int ans; cin >> ans;
        x |= (ans & 1) << b;
    }

    int m = x & (-x);
    vector<int> bs;
    for (int i = 0; i < N - 1; i++)
        if (i & m)
            bs.push_back(i);

    int v1 = *partition_point(bs.begin(), bs.end(), [&](int k) {
        cout << "? ";
        for (int i = 0; i < N - 1; i++)
            cout << ((i & m) && (i <= k)) << ' ';
        cout << endl;

        int ans; cin >> ans;
        return (ans & 1) == 0;
    });

    int v2 = v1 ^ x;

    auto dst = [&](auto &&dst, int node, int tgt, int par = -1, int d = 0) -> int {
        if (node == tgt) return d;

        for (auto x: adj[node]) {
            if (x != par) {
                int rec = dst(dst, x, tgt, node, d + 1);
                if (rec != -1)
                    return rec;
            }
        }
        return -1;
    };

    auto [d, a, b] = max({
        make_tuple(dst(dst, edges[v1].first, edges[v2].first), edges[v1].first, edges[v2].first),
        make_tuple(dst(dst, edges[v1].second, edges[v2].first), edges[v1].second, edges[v2].first),
        make_tuple(dst(dst, edges[v1].first, edges[v2].second), edges[v1].first, edges[v2].second),
        make_tuple(dst(dst, edges[v1].second, edges[v2].second), edges[v1].second, edges[v2].second),
    });

    cout << "! " << a + 1 << ' ' << b + 1 << '\n';
}
