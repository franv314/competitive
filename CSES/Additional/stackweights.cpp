#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    struct Node {
        int ma, mi;
        int lazy;
        int nb, ne;
        Node *lc, *rc;
        
        void update() {
            if (lazy) {
                ma += lazy;
                mi += lazy;
                if (nb + 1 != ne) {
                    lc->lazy += lazy;
                    rc->lazy += lazy;
                }
                lazy = 0;
            }
        }
        
        Node (int nb, int ne, Node *lc, Node *rc) :
            ma(0), mi(0), lazy(0), nb(nb), ne(ne), lc(lc), rc(rc) { }
    } *root;
    
    Node *build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(nb, ne, NULL, NULL);
        return new Node(nb, ne, build(nb, (nb + ne) / 2), build((nb + ne) / 2, ne));
    }
    
    void add(int l, int r, int d, Node *node) {
        node->update();
        if (node->ne <= l || node->nb >= r) return;
        if (l <= node->nb && node->ne <= r) {
            node->lazy = d;
            node->update();
            return;
        }
        add(l, r, d, node->lc);
        add(l, r, d, node->rc);
        node->mi = min(node->lc->mi, node->rc->mi);
        node->ma = max(node->lc->ma, node->rc->ma);
    }
    
public:

    pair<int, int> query() {
        root->update();
        return {root->mi, root->ma};
    }
    void add(int l, int r, int d) { add(l, r, d, root); }
    SegTree(int size) { root = build(1, size + 1); }
};

int main() {
    int n; cin >> n;
    SegTree segtree(n);
    while (n--) {
        int c, s; cin >> c >> s;
        if (s == 1) segtree.add(1, c + 1, 1);
        if (s == 2) segtree.add(1, c + 1, -1);
        
        auto [mi, ma] = segtree.query();
        if (mi >= 0) cout << ">\n";
        else if (ma <= 0) cout << "<\n";
        else cout << "?\n";
    }
}