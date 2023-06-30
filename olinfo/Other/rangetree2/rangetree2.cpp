#include <bits/stdc++.h>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

bool is_query;
int N, Q, A, B;

struct Node {
    valarray<int> value;
    int lazy;

    int nb, ne;
    Node *lc, *rc;

    void update() {
        if (nb + 1 != ne) {
            lc->lazy += lazy;
            rc->lazy += lazy;
        }
        value = value.cshift(lazy);
        lazy = 0;
    }
};

class Seg1D {
    Node *tree, *root;
    int nodes;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            tree[nodes] = {valarray<int>({1, 0, 0}), 0, nb, ne, NULL, NULL};
            return &tree[nodes++];
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        tree[nodes] = {lc->value + rc->value, 0, nb, ne, lc, rc};
        return &tree[nodes++];
    }

    void add(int l, int r, Node* node) {
        node->update();
        if (node->nb >= r || node->ne <= l) return;
        if (l <= node->nb && node->ne <= r) {
            node->value = node->value.cshift(-1);
            if (node->nb + 1 != node->ne) {
                node->lc->lazy--;
                node->rc->lazy--;
            }
            return;
        }
        add(l, r, node->lc);
        add(l, r, node->rc);
        node->value = node->lc->value + node->rc->value;
    }

    int query(int l, int r, Node* node) {
        node->update();
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->value[0];
        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    void add(int l, int r) {
        add(l, r, root);
    }

    int query(int l, int r) {
        return query(l, r, root);
    }

    Seg1D(int n) {
        nodes = 0;
        tree = (Node*)malloc(2000000 * sizeof(Node));
        root = build(0, n);
    }
};

int main() {
    in >> N >> Q;
    Seg1D tree(N);

    while (Q--) {
        in >> is_query >> A >> B;
        if (is_query) {
            out << tree.query(A, B + 1) << "\n";
        } else {
            tree.add(A, B + 1);
        }
    }

    return 0;
}