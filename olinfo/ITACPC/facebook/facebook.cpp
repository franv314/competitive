#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2000;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;

    vector<bitset<MAXN>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].set(v);
        adj[v].set(u);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if ((adj[i] & adj[j]).count() >= k)
                return cout << "YES\n", 0;
    
    cout << "NO\n";
}