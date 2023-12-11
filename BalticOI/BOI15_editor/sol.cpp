#include <bits/stdc++.h>
using namespace std;
 
class SegTree {
    struct Node {
        int level;
        int edit;

        Node *lc, *rc;
 
        Node(int level, int edit, Node *lc, Node *rc) :
            level(level), edit(edit), lc(lc), rc(rc) { }
    };
 
    vector<Node*> roots;
    int size;
    int idx;
    
    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(INT_MAX, false, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return new Node(INT_MAX, false, lc, rc);
    }
 
    int find_op(int level, Node *node, int nb, int ne) {
        if (nb + 1 == ne) return nb;
        if (node->rc->level < level) return find_op(level, node->rc, (nb + ne) / 2, ne);
        return find_op(level, node->lc, nb, (nb + ne) / 2);
    }
 
    Node *copy(int l, int r, Node *source, Node *target, int nb, int ne) {
        if (ne <= l || nb >= r) return target;
        if (l <= nb && ne <= r) return source;
 
        Node *lc = copy(l, r, source->lc, target->lc, nb, (nb + ne) / 2);
        Node *rc = copy(l, r, source->rc, target->rc, (nb + ne) / 2, ne);
        return new Node(min(lc->level, rc->level), rc->edit ?: lc->edit, lc, rc);
    }
 
    Node *update(int pos, int op, Node *node, int nb, int ne) {
        if (ne <= pos || nb > pos) return node;
        if (nb + 1 == ne)
            return new Node(op < 0 ? -op : 0, op > 0 ? op : 0, NULL, NULL);
        
        Node *lc = node->lc;
        Node *rc = node->rc;
 
        if (pos >= (nb + ne) / 2) rc = update(pos, op, node->rc, (nb + ne) / 2, ne);
        else lc = update(pos, op, node->lc, nb, (nb + ne) / 2);
 
        return new Node(min(lc->level, rc->level), rc->edit ?: lc->edit, lc, rc);
    }
 
public:
 
    int apply(int op) {
        if (op > 0) {
            roots.push_back(update(idx, op, roots.back(), 0, size));
        } else {
            int undone = find_op(-op, roots.back(), 0, size);
            Node *temp = copy(0, undone + 1, roots[undone], roots.back(), 0, size);
            roots.push_back(update(idx, op, temp, 0, size));
        }
 
        idx++;
        return roots.back()->edit;
    }
 
    SegTree(int size) : size(size), idx(0) {
        roots.push_back(build(0, size));
    }
};
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
 
    SegTree segtree(n);
    while (n--) {
        int a; cin >> a;
        cout << segtree.apply(a) << '\n';
    }
}