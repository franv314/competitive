#include <bits/stdc++.h>
using namespace std;

class SegTree {
    struct Node {
        int am;
        int nb, ne;

        Node *lc, *rc;

        Node (int b, int e, Node *l, Node *r) :
            am(0), nb(b), ne(e), lc(l), rc(r) { }
    } *root;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            return new Node(nb, ne, NULL, NULL);
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return new Node(nb, ne, lc, rc);
    }

    void add(int x, int v, Node *node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->am += v;
            return;
        }
        add(x, v, node->lc);
        add(x, v, node->rc);
        node->am = node->lc->am + node->rc->am;
    }

    int query(int l, int r, Node *node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->am;

        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    void add(int x, int v) { add(x, v, root); }
    int query(int l, int r) { return query(l, r, root); }

    SegTree(int size) {
        root = build(0, size);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int curr_cost = 0;
        SegTree tree(n + 1);
        for (int _ = 0; _ < n; _++) {
            int x; cin >> x;
            tree.add(x, 1);
            if (tree.query(0, x + 1) <= x) {
                curr_cost -= tree.query(x + 1, n + 1);
                curr_cost += x - tree.query(0, x + 1);
            }

            cout << curr_cost << " ";
        }
        cout << "\n";
    }
}