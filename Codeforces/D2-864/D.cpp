#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'001

struct Compare {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    }
};

int importance[MAXN];
vector<int> adj[MAXN];

int ssize[MAXN];
long long sum[MAXN];
int parent[MAXN];
set<pair<int, int>, Compare> children[MAXN];

void dfs(int node, int par = 0) {
    parent[node] = par;
    ssize[node] = 1;
    sum[node] = importance[node];

    for (auto c: adj[node]) {
        if (c == par) continue;
        dfs(c, node);

        children[node].insert({ssize[c], c});

        ssize[node] += ssize[c];
        sum[node] += sum[c];
    }
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> importance[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);
    while (m--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            cout << sum[x] << "\n";
        } else {
            if (children[x].empty()) continue;
            auto [s, heavy] = *children[x].begin();
            
            children[parent[x]].erase({ssize[x], x});
            children[parent[x]].insert({ssize[x], heavy});

            children[x].erase({ssize[heavy], heavy});
            ssize[x] -= ssize[heavy];
            sum[x] -= sum[heavy];

            children[heavy].insert({ssize[x], x});
            ssize[heavy] += ssize[x];
            sum[heavy] += sum[x];

            parent[heavy] = parent[x];
            parent[x] = heavy;
        }
    }
}