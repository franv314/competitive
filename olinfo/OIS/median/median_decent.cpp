// O(Nlog^3N) solution

#include <bits/stdc++.h>
using namespace std;

#define MAXN 50'001

struct Edge {
    int u, v, w;
};

class SegTree {
    struct Node {
        int val;
        bool reset;
        int nb, ne;
        Node *lc, *rc;

        void update() {
            if (reset) {
                val = 0;
                if (nb + 1 != ne) {
                    lc->nb = nb;
                    lc->ne = rc->nb = (nb + ne) / 2;
                    rc->ne = ne;
                    lc->reset = rc->reset = true;
                }
                reset = false;
            }
        }

        Node(int b, int e, Node *l, Node *r) :
            val(0), nb(b), ne(e), lc(l), rc(r) { }
    } *root;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            return new Node(nb, ne, NULL, NULL);
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return new Node(nb, ne, lc, rc);
    }

    void update(int x, int d, Node *node) {
        node->update();
        if (node->nb > x || node->ne <= x) return;
        node->val += d;
        if (node->nb + 1 != node->ne) {
            update(x, d, node->lc);
            update(x, d, node->rc);
        }
    }

    int query(int l, int r, Node *node) {
        node->update();
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    void reset(int size) {
        root->nb = -size;
        root->ne = size + 1;
        root->reset = true;
    }
    void update(int x, int d) { update(x, d, root); }
    int query(int l, int r) { return query(l, r, root); }

    SegTree(int size) { root = build(-size, size + 1); }

} segtree(MAXN);

class Tree {
    int size, centroid;
    vector<vector<pair<int, int>>> adj;
    vector<int> parent, subtree_size;
    vector<Tree*> decomposed;

    void get_edges(int node, int came_from, vector<Edge> &edges, int &taken) {
        int me = taken;
        for (auto [child, weight]: adj[node]) {
            if (child != came_from) {
                ++taken;
                edges.push_back({me, taken, weight});
                get_edges(child, node, edges, taken);
            }
        }
    }

    int get_centroid(int node = 0, int came_from = -1) {
        for (auto [child, _]: adj[node]) {
            if (child != came_from && subtree_size[child] * 2 > size) {
                return get_centroid(child, node);
            }
        }
        return node;
    }

    int get_sizes(int node = 0, int came_from = -1, int weight = -1) {
        subtree_size[node] = 1;
        parent[node] = came_from;

        for (auto [child, weight]: adj[node]) {
            if (child != came_from) {
                subtree_size[node] += get_sizes(child, node, weight);
            }
        }
        return subtree_size[node];
    }

    void decompose() {
        get_sizes();
        centroid = get_centroid();

        vector<Edge> edges; int temp;

        int count = 0;
        for (auto [child, _]: adj[centroid]) {
            edges.clear(); temp = 0;
            get_edges(child, centroid, edges, temp);
            decomposed.push_back(new Tree(edges));
        }
    }

    void dfs_d(int median, int node, int came_from, int curr_d) {
        segtree.update(curr_d, 1);
        for (auto [child, weight]: adj[node]) {
            if (child != came_from) {
                int add = weight > median ? 1 : -1;
                dfs_d(median, child, node, curr_d + add);
            }
        }
    }

    int dfs_c(int median, int node, int came_from, int curr_d) {
        int ret = segtree.query(-size, 1 - curr_d);
        for (auto [child, weight]: adj[node]) {
            if (child != came_from) {
                int add = weight > median ? 1 : -1;
                ret += dfs_c(median, child, node, curr_d + add);
            }
        }
        return ret;
    }

public:

    int query(int median) {
        if (size == 1) return 0;
        segtree.reset(size);
        segtree.update(0, 1);

        int count = 0;
        for (auto [child, weight]: adj[centroid]) {
            count += dfs_c(median, child, centroid, weight > median ? 1 : -1);
            dfs_d(median, child, centroid, weight > median ? 1 : -1);
        }

        for (auto d: decomposed) {
            count += d->query(median);
        }
        return count;
    }

    Tree(vector<Edge> edges) {
        size = edges.size() + 1;
        adj.resize(size);
        parent.resize(size);
        subtree_size.resize(size);

        for (int i = 0; i < edges.size(); i++) {
            adj[edges[i].u].push_back({edges[i].v, edges[i].w});
            adj[edges[i].v].push_back({edges[i].u, edges[i].w});
        }

        if (size > 1) {
            decompose();
        }
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, K; cin >> N >> K;

    vector<Edge> edges(N - 1);

    for (int i = 0; i < N - 1; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b){ return a.w < b.w; });
    vector<int> ans(N - 1);

    for (int i = 0; i < N - 1; i++) {
        ans[i]  = edges[i].w;
        edges[i].w = i;
    }

    Tree tree(edges);
    int l = 0, r = N - 1;
    while (l < r - 1) {
        int m = (l + r - 1) / 2;
        if (tree.query(m) < K) l = m + 1;
        else r = m + 1;
    }
    cout << ans[l];
}