#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<int> c(n);
    vector<vector<int>> adj(n);

    for (auto &x: c) cin >> x;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> ans(n);

    function<set<int>(int, int)> dfs = [&](int node, int par) {
        set<int> colors;
        colors.insert(c[node]);

        for (auto x: adj[node]) {
            if (x == par) continue;
            set<int> colors_2 = dfs(x, node);
            if (colors.size() < colors_2.size()) swap(colors, colors_2);

            colors.merge(colors_2);
        }
        ans[node] = colors.size();

        return colors;
    };

    dfs(0, -1);

    for (auto x: ans) cout << x << ' ';
}