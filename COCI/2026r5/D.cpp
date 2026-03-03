#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int N; cin >> N;
    vector<vector<int>> adj(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    int root = find_if(adj.begin(), adj.end(), [&](auto &it) { return it.size() > 1; }) - adj.begin();

    vector<vector<int>> by_root(N);
    vector<int> order;
    int cnt = 0;

    auto dfs = [&](auto &&dfs, int node, int d = 0, int par = -1) -> void {
        if (par != -1) by_root[par].push_back(node);
        if (d % 2) cnt++;
        else order.push_back(node);

        for (auto x: adj[node])
            if (x != par)
                dfs(dfs, x, d + 1, node);
    };

    dfs(dfs, root);

    if (cnt < N / 2) {
        root = *find_if(adj[root].begin(), adj[root].end(), [&](int it) { return adj[it].size() > 1; });
        by_root.assign(N, vector<int>());
        order.clear();
        dfs(dfs, root);
        
        assert(cnt >= N / 2);
    }

    vector<int> perm(N, -1);
    int next_up = N / 2;
    int el1, er1;
    bool side = false;
    for (auto x: order) {
        if (by_root[x].empty()) continue;
        if (x == root) {
            perm[0] = root;
            for (auto ch: by_root[root]) {
                perm[next_up] = ch;
                next_up--;
                if (next_up == 0) goto out;
            }
            el1 = 1;
            er1 = N / 2 + 1;
        } else if (side) {
            perm[el1] = x;
            for (auto ch: by_root[x]) {
                perm[el1 + next_up] = ch;
                next_up--;
                if (next_up == 0) goto out;
            }
            el1++;
            side = false;
        } else {
            perm[er1] = x;
            for (auto ch: by_root[x]) {
                perm[er1 + next_up] = ch;
                next_up--;
                if (next_up == 0) goto out;
            }
            er1++;
            side = true;
        }
    }
    out:;


    vector<int> missing(N);
    iota(missing.begin(), missing.end(), 0);
    for (auto x: perm) {
        auto it = find(missing.begin(), missing.end(), x);
        if (it != missing.end()) missing.erase(it);
    }

    for (auto &x: perm) {
        if (x == -1) {
            x = missing.back();
            missing.pop_back();
        }
    }

    for (int i = 0; i < N; i++) {
        for (auto x: perm) cout << x + 1 << ' '; cout << '\n';
        rotate(perm.begin(), perm.begin() + 1, perm.end());
    }
}