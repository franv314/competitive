#include <bits/stdc++.h>
using namespace std;

class SegTree {
    struct Node {
        long long val, lazy;
        int nb, ne;
        Node *lc, *rc;

        void update() {
            if (nb + 1 != ne && lc == NULL) {
                lc = new Node(nb, (nb + ne) / 2, NULL, NULL);
                rc = new Node((nb + ne) / 2, ne, NULL, NULL);
            }
            if (lazy) {
                val += lazy;
                if (nb + 1 != ne) {
                    lc->lazy += lazy;
                    rc->lazy += lazy;
                }
                lazy = 0;
            }
        }

        Node (int b, int e, Node *l, Node *r) :
            val(0), lazy(0), nb(b), ne(e), lc(l), rc(r) { }
    } *root;

    void add(int l, int r, int v, Node *node) {
        node->update();
        //cout << node->nb << " " << node->ne << endl;
        if (node->nb >= r || node->ne <= l) return;
        if (l <= node->nb && node->ne <= r) {
            node->lazy += v;
            node->update();
            return;
        }

        add(l, r, v, node->lc);
        add(l, r, v, node->rc);
        node->val = max(node->lc->val, node->rc->val);
    }

    long long query(int l, int r, Node *node) {
        //cout << "q " << node->nb << " " << node->ne << " " << node->val << " " << node->lazy << endl;
        node->update();
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;

        return max(
            query(l, r, node->lc),
            query(l, r, node->rc)
        );
    }

public:

    void add(int l, int r, int v) { add(l, r, v, root); }
    long long query(int l, int r) { return query(l, r, root); }

    SegTree(int N) { root = new Node(0, N, NULL, NULL); }
};

int organizza(int N, int X, int Y, vector<int> A, vector<int> B) {
    SegTree tree(1e9 + 1);

    tree.add(0, 1e9 + 1, N);
    for (int i = 0; i < N; i++) {
        tree.add(A[i], B[i] + 1, -1);
    }
    return tree.query(X, Y + 1);
}
