#include <bits/stdc++.h>
using namespace std;

#define MAXN 500'001

class SegTree {
    struct Node {
        bool val;
        optional<bool> lazy;
        int nb, ne;
        Node *lc, *rc;

        void update() {
            if (lazy) {
                val = lazy.value();
                if (nb + 1 != ne)
                    lc->lazy = rc->lazy = lazy;
                lazy = {};
            }
        }

        Node (int b, int e, Node *l, Node *r) :
            val(false), lazy(), nb(b), ne(e), lc(l), rc(r) { }
    } *root;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(nb, ne, NULL, NULL);
        return new Node(nb, ne, build(nb, (nb + ne) / 2), build((nb + ne) / 2, ne));
    }

    void update(int l, int r, bool v, Node *node) {
        node->update();

        if (node->nb >= r || node->ne <= l) return;
        if (l <= node->nb && node->ne <= r) {
            node->val = v;
            if (node->nb + 1 != node->ne)
                node->lc->lazy = node->rc->lazy = v;
            return;
        }
        update(l, r, v, node->lc);
        update(l, r, v, node->rc);
    }

    bool query(int x, Node* node) {
        node->update();

        if (node->nb > x || node->ne <= x) return false;
        if (node->nb + 1 == node->ne) return node->val;

        return query(x, node->lc) || query(x, node->rc);
    }

public:

    void update(int l, int r, bool v) { update(l, r, v, root); }
    bool query(int x) { return query(x, root); }

    SegTree(int size) { root = build(0, size); }

};

vector<int> adj[2 * MAXN];
int dfs_order;
pair<int, int> pos_in_dfs[2 * MAXN];

void dfs(int node) {
    pos_in_dfs[node].first = dfs_order++;
    for (auto child: adj[node])
        dfs(child);
    pos_in_dfs[node].second = dfs_order;
}

int main() {
    int D, P, E; cin >> D >> P >> E;

    for (int i = 0; i < D + P; i++) {
        int A; cin >> A;
        if (A >= 0)
            adj[A].push_back(i);
    }

    dfs(0);

    SegTree segtree(D + P);

    while (E--) {
        int T, ID; cin >> T >> ID;
        auto [l, r] = pos_in_dfs[ID];
        if (T == 0) segtree.update(l, r, false);
        if (T == 1) segtree.update(l, r, true);
        if (T == 2) cout << segtree.query(l) << "\n";
    }
}