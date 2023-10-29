#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> depths(n);
    vector<vector<int>> adj(n);
    vector<vector<int>> bin_lift(n);

    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    function<void(int, int, int)> dfs = [&](int node, int par, int d) {
        depths[node] = d;
        int curr = par;
        for (int h = 0; curr != -1; h++) {
            bin_lift[node].push_back(curr);
            curr = bin_lift[curr].size() > h ? bin_lift[curr][h] : -1;
        }

        for (auto c: adj[node]) {
            if (c == par) continue;
            dfs(c, node, d + 1);
        }
    };

    auto query = [&](int a, int b) {
        if (depths[a] > depths[b]) swap(a, b);

        for (int i = bin_lift[b].size() - 1; i >= 0; i--) {
            if (i < bin_lift[b].size() && depths[bin_lift[b][i]] >= depths[a]) {
                b = bin_lift[b][i];
            }
        }

        if (a == b) return a;

        for (int i = bin_lift[a].size() - 1; i >= 0; i--) {
            if (i < bin_lift[a].size() && bin_lift[a][i] != bin_lift[b][i]) {
                a = bin_lift[a][i];
                b = bin_lift[b][i];
            }
        }

        return bin_lift[a][0];
    };

    dfs(0, -1, 0);
    while (q--) {
        int a, b; cin >> a >> b;
        a--, b--;
        int lca = query(a, b);

        cout << depths[a] + depths[b] - 2 * depths[lca] << '\n'; 
    }
}