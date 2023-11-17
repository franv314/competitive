#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    function<int(int, int, int)> dfs = [&](int node, int par, int m) -> int {
        vector<int> child_paths;
        for (auto x: adj[node]) {
            if (x == par) continue;
            int p = dfs(x, node, m);
            if (p == -1) return -1;
            child_paths.push_back(p + 1);
        }
        sort(child_paths.begin(), child_paths.end());

        if (node == 0) {
            multiset<int> vals(child_paths.begin(), child_paths.end());
            while (!vals.empty() && *vals.begin() < m) {
                int val = *vals.begin();
                vals.erase(vals.begin());
                auto it = vals.lower_bound(m - val);
                if (it == vals.end()) {
                    return 0;
                } else {
                    vals.erase(it);
                }
            }

            return 1;
        }

        int l = -1, r = child_paths.size();
        while (l + 1 < r) {
            int M = (l + r) / 2;

            vector<int> things = child_paths;
            things.erase(things.begin() + M);

            multiset<int> vals(things.begin(), things.end());
            while (!vals.empty() && *vals.begin() < m) {
                int val = *vals.begin();
                vals.erase(vals.begin());
                auto it = vals.lower_bound(m - val);
                if (it == vals.end()) {
                    r = M;
                    goto next;
                } else {
                    vals.erase(it);
                }
            }

            l = M;
            next:;
        }

        if (l != -1) return child_paths[l];
        if (child_paths.size() & 1) return -1;

        for (int i = 0; i < child_paths.size() / 2; i++) {
            if (child_paths[i] + child_paths[child_paths.size() - 1 - i] < m) {
                return -1;
            }
        }
        return 0;
    };

    int l = 0, r = N;
    while (l + 1 < r) {
        int m = (l + r) / 2;

        int val = dfs(0, -1, m);
        if (val == 1) l = m;
        else r = m;
    }

    cout << l << '\n';
}