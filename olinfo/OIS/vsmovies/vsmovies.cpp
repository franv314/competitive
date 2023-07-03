#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> nodes;
    
    void join(int u, int v) {
        u = find(u), v = find(v);
        if (nodes[u] > nodes[v]) swap(u, v);
        
        nodes[u] += nodes[v];
        nodes[v] = u;
    }
    
    int find(int node) {
        if (nodes[node] < 0) return node;
        return nodes[node] = find(nodes[node]);
    }
    
    DSU(int n) : nodes(n, -1) { }  
};

class SegTree {
    struct Node {
        int val;
        int nb, ne;
        Node *lc, *rc;
        
        Node(int nb, int ne, Node *lc, Node *rc) : nb(nb), ne(ne), lc(lc), rc(rc) { }
    } *root;
    
    Node *build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(nb, ne, NULL, NULL);
        return new Node(nb, ne, build(nb, (nb + ne) / 2), build((nb + ne) / 2, ne));
    }
    
    void set(int x, int v, Node *node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->val = v;
            return;
        }
        set(x, v, node->lc);
        set(x, v ,node->rc);
        node->val = max(node->lc->val, node->rc->val);
    }
    
    int query(int l, int r, Node *node) {
        if (node->nb >= r || node->ne <= l) return INT_MIN;
        if (l <= node->nb && node->ne <= r) return node->val;
        return max(query(l, r, node->lc), query(l, r, node->rc));
    }
    
public:
    void set(int x, int v) { set(x, v, root); }
    int query(int l, int r) { return query(l, r, root); }
    SegTree(int size) { root = build(0, size); }
};

int main() {
    int N, S; cin >> N >> S;
    vector<tuple<int, int, int>> edges(N), edges2;
    for (auto &[t, a, b]: edges) {
        cin >> a >> b >> t;
    }
    
    edges2 = edges;
    sort(edges2.begin(), edges2.end());
    map<pair<int, int>, int> edges_in_mst;
    DSU dsu(S);
    long long mst_weight = 0;
    vector<vector<pair<int, int>>> adj(S);
    vector<tuple<int, int, int>> mst;
    
    for (auto [t, a, b]: edges2) {
        if (dsu.find(a) != dsu.find(b)) {
            dsu.join(a, b);
            mst.push_back({t, a, b});
            edges_in_mst[{a, b}] = t;
            adj[a].push_back({b, t});
            adj[b].push_back({a, t});
            mst_weight += t;
        }
    }
    
    vector<vector<pair<int, int>>> binlift(S);
    vector<int> depths(S);
    vector<int> path;
    SegTree segtree(S);
    function<void(int, int, int)> dfs = [&](int node, int parent, int depth) {
        depths[node] = depth;
        path.push_back(node);
        for (int i = 0; (1 << i) <= depth; i++) {
            binlift[node].push_back({path[path.size() - 1 - (1 << i)], segtree.query(depth - (1 << i), depth)});
        }
        for (auto [n, t]: adj[node]) {
            if (n == parent) continue;
            segtree.set(depth, t);
            dfs(n, node, depth + 1);
        }
        path.pop_back();
    };
    
    function<int(int, int)> lca = [&](int u, int v) -> int {
        if (depths[u] > depths[v]) swap(u, v);
        
        int ma = INT_MIN;
        for (int i = binlift[v].size() - 1; i >= 0; i--) {
            if (i < binlift[v].size() && depths[binlift[v][i].first] >= depths[u]) {
                ma = max(ma, binlift[v][i].second);
                v = binlift[v][i].first;
            }
        }
        
        if (u == v) return ma;
        
        for (int i = binlift[u].size() - 1; i >= 0; i--) {
            if (i < binlift[u].size() && binlift[u][i].first != binlift[v][i].first) {
                ma = max(ma, binlift[u][i].second);
                ma = max(ma, binlift[v][i].second);
                u = binlift[u][i].first;
                v = binlift[v][i].first;
            }
        }
        
        return max({ma, binlift[u][0].second, binlift[v][0].second});
    };
    
    dfs(0, -1, 0);
    
    for (auto [t, a, b]: edges) {
        if (edges_in_mst.count({a, b})) {
            cout << mst_weight + t - edges_in_mst[{a, b}] << '\n';
        } else {
            cout << mst_weight + t - lca(a, b) << '\n';
        }
    }
}