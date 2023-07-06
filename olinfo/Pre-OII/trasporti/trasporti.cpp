#include <bits/stdc++.h>
using namespace std;

#define MAXN 100001

struct SegmentInfo {
    int ma;
    SegmentInfo(int ma) : ma(ma) { }
};

SegmentInfo merge(SegmentInfo a, SegmentInfo b) {
    return { max(a.ma, b.ma) };
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

void solve(int N, int Q, int *briganti, int *A, int *B, int *start, int *end, int *sol) {
    vector<int> nodes(briganti, briganti + N);
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }
    
    vector<vector<pair<int, SegmentInfo>>> binlift(nodes.size());
    vector<int> depths(nodes.size());
    
    vector<int> path;
    
    function<void(int, int)> dfs = [&](int node, int parent) {
        int depth = path.size();
        depths[node] = depth;
        segtree.set(depth, nodes[node]);
        path.push_back(node);
        
        for (int i = 0; (1 << i) <= depth; i++) {
            binlift[node].push_back({path[depth - (1 << i)], segtree.query(depth - (1 << i) + 1, depth + 1)});
        }
        
        for (auto c: adj[node]) {
            if (c != parent)
                dfs(c, node);
        }
        path.pop_back();
        segtree.set(depth, 0);
    };
    
    dfs(0, -1);
    
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
        
        return merge(sv, merge({nodes[lca]}, su));
    };
    
    for (int q = 0; q < Q; q++) {  
        SegmentInfo ans = lca(start[q], end[q]);
        sol[q] = ans.ma;
    }
}