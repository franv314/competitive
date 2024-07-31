#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    
    vector<vector<int>> dadj(n);
    vector<vector<int>> radj(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        dadj[u - 1].push_back(v - 1);
        radj[v - 1].push_back(u - 1);
    }

    vector<bool> visited(n);
    vector<int> cc(n, -1), scc(n, -1);
    
    vector<int> q;

    auto dfs1 = [&](auto &&dfs1, int x) {
        if (visited[x]) return;
        visited[x] = true;

        for (auto y: dadj[x])
            dfs1(dfs1, y);
        
        q.push_back(x);
    };

    auto dfs2 = [&](auto &&dfs2, int x, int root) {
        if (scc[x] != -1) return;
        scc[x] = root;

        for (auto y: radj[x])
            dfs2(dfs2, y, root);
    };

    auto dfs3 = [&](auto &&dfs3, int x, int root) {
        if (cc[x] != -1) return;
        cc[x] = root;

        for (auto y: dadj[x])
            dfs3(dfs3, y, root);
        for (auto y: radj[x])
            dfs3(dfs3, y, root);
    };

    for (int i = 0; i < n; i++)
        dfs1(dfs1, i);
    reverse(q.begin(), q.end());
    for (auto i: q)
        dfs2(dfs2, i, i);
    for (int i = 0; i < n; i++)
        dfs3(dfs3, i, i);

    vector<vector<int>> ccs(n);
    vector<int> sccf(n);
    for (int i = 0; i < n; i++) {
        ccs[cc[i]].push_back(i);
        sccf[scc[i]]++;
    }
    
    int total = 0;
    for (auto ccx: ccs) {
        if (ccx.empty()) continue;

        total += ccx.size() - 1;
        
        for (auto x: ccx) {
            if (sccf[scc[x]] > 1) {
                total++;
                break;
            }
        }
    }

    cout << total << '\n';
}