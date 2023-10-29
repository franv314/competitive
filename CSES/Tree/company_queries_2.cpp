#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> p(n, -1);
    vector<int> depths(n);
    vector<vector<int>> adj(n);
    vector<vector<int>> bin_lift(n);

    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        adj[p[i]].push_back(i);
    }

    function<void(int, int)> dfs = [&](int node, int d) {
        depths[node] = d;
        int curr = p[node];
        for (int h = 0; curr != -1; h++) {
            bin_lift[node].push_back(curr);
            curr = bin_lift[curr].size() > h ? bin_lift[curr][h] : -1;
        }

        for (auto c: adj[node]) {
            dfs(c, d + 1);
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

        return p[a];
    };

    dfs(0, 0);
    while (q--) {
        int a, b; cin >> a >> b;
        cout << 1 + query(a - 1, b - 1) << '\n';
    }
}