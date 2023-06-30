#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

class SegTree {
    struct Node {
        int val;
        int nb, ne;
        Node *lc, *rc;

        Node(int b, int e, Node *l, Node *r) :
            val(0), nb(b), ne(e), lc(l), rc(r) { }
    } *root;

    Node *build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(nb, ne, NULL, NULL);
        return new Node(nb, ne, build(nb, (nb + ne) / 2), build((nb + ne) / 2, ne));
    }

    void update(int x, int v, Node *node) {
        if (node->nb > x || node->ne <= x) return;

        node->val = max(node->val, v);
        if (node->nb + 1 == node->ne) return;
        update(x, v, node->lc);
        update(x, v, node->rc);

    }

    int query(int l, int r, Node *node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return max(query(l, r, node->lc), query(l, r, node->rc));
    }

public:

    void update(int x, int v) { update(x, v, root); }
    int query(int l, int r) { return query(l, r, root); }

    SegTree(int size) { root = build(0, size); }

};

int main() {
    int N; cin >> N;
    
    vector<int> P(N);
    for (auto &p: P) cin >> p;

    vector<int> C(N + 1);
    for (int i = 1; i <= N; i++) cin >> C[i];

    SegTree segtree(N + 1);
    for (int i = N - 1; i >= 0; i--) {
        int longest = 1 + max(
            segtree.query(P[i] + 1, N + 1),
            segtree.query(C[P[i]], C[P[i]] + 1)
        );

        segtree.update(P[i], longest);
    }
    cout << segtree.query(0, N + 1) << "\n";
}