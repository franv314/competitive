#include <bits/stdc++.h>
#include "supertrees.h"
using namespace std;

struct DSU {
    vector<int> nodes;

    int find(int node) {
        if (nodes[node] < 0) return node;
        return nodes[node] = find(nodes[node]);
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (nodes[u] > nodes[v]) swap(u, v);
        nodes[u] += nodes[v];
        nodes[v] = u;
    }

    map<int, vector<int>> get_cc() {
        map<int, vector<int>> ans;
        for (int i = 0; i < nodes.size(); i++) {
            ans[find(i)].push_back(i);
        }
        return ans;
    }

    DSU(int size) : nodes(size, -1) { }
};

int construct(vector<vector<int>> p) {
    int n = p.size();
    
    vector adj(n, vector(n, 0));
    vector act_p(n, vector(n, 0));
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i][j] == 3) return 0;
            if (p[i][j]) dsu.join(i, j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dsu.find(i) == dsu.find(j) && p[i][j] == 0) {
                return 0;
            }
        }
    }

    auto ccs = dsu.get_cc();
    for (auto [_, cc]: ccs) {
        bool found2 = false;
        DSU dsu2(cc.size());
        for (int i = 0; i < cc.size(); i++) {
            for (int j = 0; j < cc.size(); j++) {
                if (p[cc[i]][cc[j]] == 1) dsu2.join(i, j);
                if (p[cc[i]][cc[j]] == 2) found2 = true;
            }
        }
        for (int i = 0; i < cc.size(); i++) {
            for (int j = 0; j < cc.size(); j++) {
                //cout << i << " " << j << " " << dsu2.find(i) << " " << dsu2.find(j) << endl;
                if (dsu2.find(i) == dsu2.find(j) && p[cc[i]][cc[j]] == 2) return 0;
            }
        }

        auto ccs2 = dsu2.get_cc();
        vector<int> cycle;
        for (auto [r, cc2]: ccs2) {
            cycle.push_back(cc[r]);
            for (int i = 1; i < cc2.size(); i++) {
                adj[cc[cc2[i]]][cc[cc2[i - 1]]] = adj[cc[cc2[i - 1]]][cc[cc2[i]]] = 1;
            }
        }
        if (cycle.size() < 3) {
            if (found2) return 0;
            else continue;
        }
        for (int i = 0; i < cycle.size(); i++) {
            adj[cycle[i]][cycle[(i + 1) % cycle.size()]] = adj[cycle[(i + 1) % cycle.size()]][cycle[i]] = 1;
        }
    }

    build(adj);
    return 1;
}