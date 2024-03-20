#include <bits/stdc++.h>
using namespace std;

#define K 10

template<typename T>
class SparseTable {
    vector<vector<T>> table;
    vector<int> logs;

public:

    T query(int l, int r) {
        int h = logs[r - l];
        return min(table[h][l], table[h][r - (1 << h)]);
    }

    SparseTable(int N, const vector<T> &arr) {
        logs.resize(N + 1);
        for (int i = 2; i <= N; i++) logs[i] = logs[i - 1] + __builtin_popcount(i) == 1;

        table.push_back(arr);
        for (int h = 1; (1 << h) <= N; h++) {
            vector<T> new_row(N);

            for (int i = 0; i < N; i++) {
                new_row[i] = min(table.back()[i], table.back()[min(N - 1, i + (1 << (h - 1)))]);
            }
            table.push_back(new_row);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<vector<int>> adj(N);
    
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> timer(N), depth(N);
    vector<pair<int, int>> dfs_order;

    auto dfs1 = [&](auto &&dfs1, int node, int par = -1, int d = 0) -> void {
        timer[node] = dfs_order.size();
        depth[node] = d;

        dfs_order.emplace_back(d, node);

        for (auto x: adj[node]) {
            if (x != par) {
                dfs1(dfs1, x, node, d + 1);
            }
            dfs_order.emplace_back(d, node);
        }
    };

    dfs1(dfs1, 0);
    SparseTable st(dfs_order.size(), dfs_order);

    long long ans_big = 0;
    for (int u = 0; u < N / K; u++) {
        for (int v = u + 1; v < N / K; v++) {
            auto [t1, t2] = minmax(timer[u], timer[v]);
            int lca = st.query(t1, t2).second;

            int dst = depth[u] + depth[v] - 2 * depth[lca];
            if (dst % (u + v) == 0 && dst / (u + v) > K) ans_big++;
        }
    }

    long long ans_small = 0;

    auto dfs2 = [&](auto &&dfs2, int node, int t, int par = -1) -> map<int, int> {
        map<int, int> curr;
        curr[depth[node] - t * node]++;

        for (auto x: adj[node]) {
            if (x == par) continue;

            map<int, int> child = dfs2(dfs2, x, t, node);
            if (child.size() > curr.size()) swap(child, curr);

            for (auto [v, f]: child) {
                if (curr.count(2 * depth[node] - v))
                    ans_small += curr[2 * depth[node] - v] * (long long)f;
            }
            
            for (auto [v, f]: child) {
                curr[v] += f;
            }
        }

        return curr;
    };

    for (int i = 1; i <= K; i++) {
        dfs2(dfs2, 0, i);
    }

    cout << ans_big + ans_small << '\n';
}