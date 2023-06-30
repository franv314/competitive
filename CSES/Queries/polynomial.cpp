#include <bits/stdc++.h>
using namespace std;

class SegTree {
    struct Node {
        long long val;
        pair<long long, long long> lazy;

        int nb, ne;
        Node *lc, *rc;

        void update() {
            auto [m, q] = lazy;
            if (m || q) {
                val += q * (ne - nb)
                     + m * ((long long)ne * (ne - 1) / 2 - (long long)nb * (nb - 1) / 2);

                if (nb + 1 != ne) {
                    lc->lazy.first += m;
                    lc->lazy.second += q;
                    rc->lazy.first += m;
                    rc->lazy.second += q;
                }

                lazy = {0, 0};
            }
        }

        Node(long long val, int nb, int ne, Node *lc, Node *rc) :
            val(val), nb(nb), ne(ne), lc(lc), rc(rc) { }
    } *root;

    Node* build(int nb, int ne, int val[]) {
        if (nb + 1 == ne) return new Node(val[nb], nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2, val);
        Node *rc = build((nb + ne) / 2, ne, val);
        return new Node(lc->val + rc->val, nb, ne, lc, rc);
    }

    void update(int l, int r, pair<int, int> upd, Node *node) {
        node->update();
        if (node->ne <= l || node->nb >= r) return;
        if (l <= node->nb && node->ne <= r) {
            node->lazy.first += upd.first;
            node->lazy.second += upd.second;
            node->update();
            return;
        }

        update(l, r, upd, node->lc);
        update(l, r, upd, node->rc);
        node->val = node->lc->val + node->rc->val;
    }

    long long query(int l, int r, Node *node) {
        node->update();
        if (node->ne <= l || node->nb >= r) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    long long query(int l, int r) { return query(l, r, root); }
    void update(int l, int r, pair<int, int> upd) { update(l, r, upd, root); }
    SegTree(vector<int> arr) { root = build(0, arr.size(), arr.data()); }
};

int main() {
    int n, q; cin >> n >> q;
    vector<int> t(n);
    for (auto &x: t) cin >> x;

    SegTree segtree(t);

    while (q--) {
        int t, a, b; cin >> t >> a >> b;
        if (t == 1) segtree.update(a - 1, b, {1, 2 - a});
        else cout << segtree.query(a - 1, b) << '\n';
    }
}