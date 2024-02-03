#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;
    vector<vector<long long>> adj(n, vector<long long>(n, 1e18));

    for (int i = 0; i < n; i++) adj[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a - 1][b - 1] = adj[b - 1][a - 1] = min(adj[a - 1][b - 1], 1LL * c);
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    
    while (q--) {
        int a, b; cin >> a >> b;
        long long dst = adj[a - 1][b - 1];

        cout << (dst == 1e18 ? -1 : dst) << '\n';
    }
}