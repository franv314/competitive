#include <bits/stdc++.h>
using namespace std;

#define MAXN 200001

struct SegmentInfo {
    int sum, max_pref, max_suff, max_sub, min_pref, min_suff, min_sub;
    
    SegmentInfo(int sum, int max_pref, int max_suff, int max_sub, int min_pref, int min_suff, int min_sub) :
        sum(sum), max_pref(max_pref), max_suff(max_suff), max_sub(max_sub), min_pref(min_pref), min_suff(min_suff), min_sub(min_sub) { }
    
    SegmentInfo(int val) {
        sum = val;
        max_pref = max_suff = max_sub = max(val, 0);
        min_pref = min_suff = min_sub = min(val, 0);
    }
};

SegmentInfo merge(SegmentInfo a, SegmentInfo b) {
    return {
        a.sum + b.sum,
        max(a.max_pref, a.sum + b.max_pref),
        max(b.max_suff, b.sum + a.max_suff),
        max({a.max_sub, b.max_sub, a.max_suff + b.max_pref}),
        min(a.min_pref, a.sum + b.min_pref),
        min(b.min_suff, b.sum + a.min_suff),
        min({a.min_sub, b.min_sub, a.min_suff + b.min_pref}),  
    };
}

struct SegTree {
    struct Node {
        SegmentInfo info;
        int nb, ne;
        Node *lc, *rc;
        
        Node(SegmentInfo info, int nb, int ne, Node *lc, Node *rc) :
            info(info), nb(nb), ne(ne), lc(lc), rc(rc) { } 
    } *root;
    
    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return new Node({0}, nb, ne, NULL, NULL);
        return new Node({0}, nb, ne, build(nb, (nb + ne) / 2), build((nb + ne) / 2, ne));
    }
    
    void set(int x, int new_val, Node *node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->info = SegmentInfo(new_val);
            return;
        }
        set(x, new_val, node->lc);
        set(x, new_val, node->rc);
        node->info = merge(node->lc->info, node->rc->info);
    }
    
    SegmentInfo query(int l, int r, Node *node) {
        if (node->nb >= r || node->ne <= l) return {0};
        if (l <= node->nb && node->ne <= r) return node->info;
        return merge(query(l, r, node->lc), query(l, r, node->rc));
    }

public:

    SegmentInfo query(int l, int r) { return query(l, r, root); }
    void set(int x, int new_val) { set(x, new_val, root); }
    SegTree() { root = build(0, MAXN); }
} segtree;

void solve() {
    int q; cin >> q;
    vector<int> nodes(1, {1});
    vector<vector<int>> adj(1);
    vector<array<int, 3>> queries;
    
    while (q--) {
        char t; cin >> t;
        if (t == '+') {
            int v, x; cin >> v >> x;
            v--;
            nodes.push_back(x);
            adj[v].push_back(adj.size());
            adj.push_back({});
        } else {
            int u, v, k; cin >> u >> v >> k;
            u--, v--;
            queries.push_back({u, v, k});
        }
    }
    
    vector<vector<pair<int, SegmentInfo>>> binlift(nodes.size());
    vector<int> depths(nodes.size());
    
    vector<int> path;
    
    function<void(int)> dfs = [&](int node) {
        int depth = path.size();
        depths[node] = depth;
        segtree.set(depth, nodes[node]);
        path.push_back(node);
        
        for (int i = 0; (1 << i) <= depth; i++) {
            binlift[node].push_back({path[depth - (1 << i)], segtree.query(depth - (1 << i) + 1, depth + 1)});
        }
        
        for (auto c: adj[node]) {
            dfs(c);
        }
        path.pop_back();
        segtree.set(depth, 0);
    };
    
    dfs(0);
    
    function<SegmentInfo(int, int)> lca = [&](int u, int v) {
        if (depths[v] < depths[u]) swap(u, v);
        SegmentInfo su(0), sv(0);
        
        for (int i = binlift[v].size() - 1; i >= 0; i--) {
            if (i < binlift[v].size() && depths[binlift[v][i].first] >= depths[u]) {
                sv = merge(binlift[v][i].second, sv);
                v = binlift[v][i].first;
            }
        }
        
        if (u == v) return merge({nodes[v]}, sv);
        
        for (int i = binlift[u].size(); i >= 0; i--) {
            if (i < binlift[u].size() && binlift[u][i].first != binlift[v][i].first) {
                su = merge(binlift[u][i].second, su);
                sv = merge(binlift[v][i].second, sv);
                u = binlift[u][i].first;
                v = binlift[v][i].first;
            }
        }
        
        su = merge(binlift[u][0].second, su);
        sv = merge(binlift[v][0].second, sv);
        int lca = binlift[u][0].first;
        
        swap(sv.max_suff, sv.max_pref);
        swap(sv.min_pref, sv.min_suff);
        return merge(sv, merge({nodes[lca]}, su));
    };
    
    for (auto [u, v, k]: queries) {  
        SegmentInfo ans = lca(u, v);
        if (ans.min_sub <= k && k <= ans.max_sub) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}