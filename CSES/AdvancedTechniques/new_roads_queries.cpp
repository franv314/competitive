#include <bits/stdc++.h>
using namespace std;
 
#define LOG(x) (31 - __builtin_clz(x))
 
template<typename T>
class SparseTable {
    vector<vector<T>> table;
 
public:
 
    pair<int, int> query(int l, int r) {
        int d = r - l;
        int h = LOG(d);
        return min(table[h][l], table[h][r - (1 << h)]);
    }
 
    SparseTable() { }
    SparseTable(vector<T> vals) : table(1 + LOG(vals.size()), vector<T>(vals.size())) {
        table[0] = vals;
        for (int h = 1; h <= LOG(vals.size()); h++) {
            for (int i = 0; i < vals.size(); i++) {
                table[h][i] = min(table[h - 1][i], table[h - 1][min((int)vals.size(), i + (1 << (h - 1)))]);
            }
        }
    }
};
 
class Tree {
    vector<vector<pair<int, int>>> children;
    vector<pair<int, int>> subtrees;
    vector<pair<int, int>> dfs_order;
    SparseTable<pair<int, int>> table;
 
    void dfs(int node, int depth) {
        subtrees[node].first = dfs_order.size();
        dfs_order.push_back({depth, node});
 
        for (auto [child, day]: children[node]) {
            dfs(child, depth + 1);
            dfs_order.push_back({depth, node});
        }
 
        subtrees[node].second = dfs_order.size();
    }
 
public:
 
    void init() {
        dfs(0, 0);
        table = SparseTable<pair<int, int>>(dfs_order);
    }
 
    int joined_at(int a, int b) {
        if (subtrees[a].second > subtrees[b].second) swap(a, b);
        int lca = table.query(subtrees[a].second, subtrees[b].second).second;
 
        int time_a = 0, time_b = 0;
        if (a != lca) {
            int l = 0, r = children[lca].size();
            while (l + 1 < r) {
                int m = (l + r) / 2;
                if (subtrees[children[lca][m].first].first > subtrees[a].first) r = m;
                else l = m;
            }
            time_a = children[lca][l].second;
        }
        if (b != lca) {
            int l = 0, r = children[lca].size();
            while (l + 1 < r) {
                int m = (l + r) / 2;
                if (subtrees[children[lca][m].first].first > subtrees[b].first) r = m;
                else l = m;
            }
            time_b = children[lca][l].second;
        }
        return max(time_a, time_b);
    }
 
    void insert_child(int parent, int child, int day) {
        children[parent].push_back({child, day});
    }
 
    Tree (int size) : children(size + 1), subtrees(size + 1) { }
};
 
class DSU {
    vector<int> arr;
    Tree tree;
 
public:
 
    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }
 
    void join(int u, int v, int day) {
        u = find(u), v = find(v);
        if (u == v) return;
 
        if (arr[u] > arr[v]) swap(u, v);
 
        arr[u] += arr[v];
        arr[v] = u;
        tree.insert_child(u, v, day);
    }
 
    void init_tree() {
        for (int i = 1; i <= arr.size(); i++)
            if (arr[i] < 0)
                tree.insert_child(0, i, -1);
        tree.init();
    }
 
    int query(int u, int v) {
        return tree.joined_at(u, v);
    }
 
    DSU(int size) : arr(size + 1, -1), tree(size) { }
};
 
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, q; cin >> n >> m >> q;
 
    DSU dsu(n);
 
    for (int day = 1; day <= m; day++) {
        int u, v; cin >> u >> v;
        dsu.join(u, v, day);
    }
    dsu.init_tree();
 
    while (q--) {
        int u, v; cin >> u >> v;
        cout << (u == v ? 0 : dsu.query(u, v)) << '\n';
    }
}