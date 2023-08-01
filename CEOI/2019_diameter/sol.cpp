#include <bits/stdc++.h>
using namespace std;

constexpr int64_t INF = 2e18;

class SegTree {
    int size;
    vector<int64_t> arr, lazy;
    
    void update(int n, int nb, int ne) {
        if (lazy[n]) {
            arr[n] += lazy[n];
            
            if (nb + 1 != ne) {
                lazy[2 * n] += lazy[n];
                lazy[2 * n + 1] += lazy[n];
            }
            
            lazy[n] = 0;
        }
    }
    
    void add(int l, int r, int64_t d, int n, int nb, int ne) {
        update(n, nb, ne);
        if (nb >= r || ne <= l) return;
        if (l <= nb && ne <= r) {
            lazy[n] = d;
            update(n, nb, ne);
            return;
        }
        add(l, r, d, 2 * n, nb, (nb + ne) / 2);
        add(l, r, d, 2 * n + 1, (nb + ne) / 2, ne);
        arr[n] = max(arr[2 * n], arr[2 * n + 1]);
    }
    
public:
    
    void add(int l, int r, int64_t d) { add(l, r, d, 1, 0, size); }
    int64_t query() {
        update(1, 0, size);
        return arr[1];
    }
    
    SegTree() {}
    SegTree(vector<int64_t> vals) {
        size = 1 << (32 - __builtin_clz(vals.size() - 1));
        arr.resize(size * 2, -INF);
        lazy.resize(size * 2);
        
        for (int i = 0; i < vals.size(); i++)
            arr[i + size] = vals[i];
        for (int i = size - 1; i > 0; i--)
            arr[i] = max(arr[2 * i], arr[2 * i + 1]);
    };
};

class Tree {
    vector<vector<tuple<int, int, int64_t>>> adj;
    
    int centroid_tree_root;
    
    vector<vector<tuple<int, int, int>>> ranges;
    vector<SegTree> segtrees;
    vector<set<pair<int64_t, int>, greater<>>> sizes, subtrees;
public:

    int64_t diameter() {
        return sizes[centroid_tree_root].begin()->first;
    }
    
    int64_t get_max_path(int c) {
        if (subtrees[c].size() > 1) return subtrees[c].begin()->first + next(subtrees[c].begin())->first;
        if (subtrees[c].size() == 1) return subtrees[c].begin()->first;
        return 0;
    }
    
    void update(int edge, int64_t d) {
        int old = -1;
        int64_t old_max_seg, old_max_path;
        for (auto [c, l, r]: ranges[edge]) {
            int64_t new_old_max_seg = segtrees[c].query();
            int64_t new_old_max_path = sizes[c].begin()->first;
            int64_t old_max_path_through = get_max_path(c);
            
            if (old != -1) {
                subtrees[c].erase({old_max_seg, old});
                sizes[c].erase({old_max_path, old});
                
                subtrees[c].emplace(segtrees[old].query(), old);
                sizes[c].emplace(sizes[old].begin()->first, old);
            }
            
            segtrees[c].add(l, r, d);
            sizes[c].erase({old_max_path_through, c});
            sizes[c].emplace(get_max_path(c), c);
            
            old_max_seg = new_old_max_seg;
            old_max_path = new_old_max_path;
            old = c;
        }
    }
    
    Tree(int n, vector<tuple<int, int, int64_t>> edges) :
        adj(n), ranges(n - 1), segtrees(n), sizes(n), subtrees(n)
    {
        for (int i = 0; i < n - 1; i++) {
            auto [u, v, w] = edges[i];
            adj[u].emplace_back(v, i ,w);
            adj[v].emplace_back(u, i, w);    
        }
        
        vector<bool> nodes(n);
        vector<int> parent(n);
        vector<int64_t> dfs_order;
        
        function<int(int, int, vector<int>&)> populate = [&](int node, int par, vector<int> &size) {
            size[node] = 1;
            for (auto [n, i, w]: adj[node]) {
                if (n == par || nodes[n]) continue;
                parent[n] = node;
                size[node] += populate(n, node, size);
            }
            return size[node];
        };
        
        function<void(int, int, int, int64_t)> get_dfs_order = [&](int node, int in_edge, int centroid, int64_t d) {
            int start = dfs_order.size();
            dfs_order.push_back(d);
            for (auto [n, i, w]: adj[node]) {
                if (i == in_edge || nodes[n]) continue;
                get_dfs_order(n, i, centroid, d + w);
            }
            
            int end = dfs_order.size();
            if (in_edge >= 0) ranges[in_edge].emplace_back(centroid, start, end);
        };
        
        function<int(int, int, int64_t)> make_centroid_tree = [&](int root, int curr_size, int64_t d) -> int {
            vector<int> size(n);
            populate(root, -1, size);
            parent[root] = -1;
            
            int centroid = root;
            for (;;) {
                bool found = true;
                for (auto [n, i, w]: adj[centroid]) {
                    if (!nodes[n] && n != parent[centroid] && 2 * size[n] > curr_size) {
                        centroid = n;
                        found = false;
                        break;
                    }
                }
                if (found) break;
            }
            
            dfs_order.clear();
            get_dfs_order(root, -1, centroid, d);
            segtrees[centroid] = SegTree(dfs_order);
            
            nodes[centroid] = true;
            
            for (auto [n, i, w]: adj[centroid]) {
                if (nodes[n]) continue;
                if (n == parent[centroid]) {
                    int c = make_centroid_tree(n, curr_size - size[centroid], w);
                    
                    ranges[i].emplace_back(c, 0, curr_size - size[centroid]);
                    
                    sizes[centroid].emplace(sizes[c].begin()->first, c);
                    subtrees[centroid].emplace(segtrees[c].query(), c);
                } else {
                    int c = make_centroid_tree(n, size[n], w);
                    
                    ranges[i].emplace_back(c, 0, size[n]);
                    
                    sizes[centroid].emplace(sizes[c].begin()->first, c);
                    subtrees[centroid].emplace(segtrees[c].query(), c);
                }
            }
            
            sizes[centroid].emplace(get_max_path(centroid), centroid);
            
            return centroid;
        };
        
        centroid_tree_root = make_centroid_tree(0, n, 0);
        for (auto &vec: ranges) {
            reverse(vec.begin(), vec.end());
        }
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    int64_t w; cin >> w;
    
    vector<int64_t> edge_weights(n - 1);
    vector<tuple<int, int, int64_t>> edges(n - 1);
    for (int i = 0; i < n - 1; i++) {
        auto &[u, v, w] = edges[i];
        
        cin >> u >> v >> w;
        u--, v--;
        
        edge_weights[i] = w;
    }
    
    Tree tree(n, edges);
    
    int64_t last = 0;
    while (q--) {
        int edge; cin >> edge;
        int64_t new_w; cin >> new_w;
        
        edge = (edge + last) % (n - 1);
        new_w = (new_w + last) % w;
        
        tree.update(edge, new_w - edge_weights[edge]);
        cout << (last = tree.diameter()) << "\n";
        
        edge_weights[edge] = new_w;
    }
}