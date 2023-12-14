#include <bits/stdc++.h>
using namespace std;

class SegTree {
    struct Node {
        long long sum;
        int nb, ne;
        Node *lc, *rc;
    
        Node(long long sum, int nb, int ne, Node *lc, Node *rc) :
            sum(sum), nb(nb), ne(ne), lc(lc), rc(rc) { }
    };
    vector<Node*> roots;

    Node* build(int nb, int ne, int arr[]) {
        if (nb + 1 == ne) return new Node(arr[nb], nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2, arr);
        Node *rc = build((nb + ne) / 2, ne, arr);
        return new Node(lc->sum + rc->sum, nb, ne, lc, rc);
    }

    Node* set(int p, int v, Node *node) {
        if (node->nb > p || node->ne <= p) return node;
        if (node->nb + 1 == node->ne) return new Node(v, node->nb, node->ne, NULL, NULL);

        Node *lc = set(p, v, node->lc);
        Node *rc = set(p, v, node->rc);
        return new Node(lc->sum + rc->sum, node->nb, node->ne, lc, rc);
    }

    long long sum(int l, int r, Node *node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->sum;
        return sum(l, r, node->lc) + sum(l, r, node->rc);
    }

public:

    void copy_array(int k) { roots.push_back(roots[k]); }
    void set(int p, int v, int k) { roots[k] = set(p, v, roots[k]); }
    long long sum(int l, int r, int k) { return sum(l, r, roots[k]); }
    SegTree(vector<int> &arr) { roots.push_back(build(0, arr.size(), arr.data())); }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    SegTree segtree(a);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int k, a, x; cin >> k >> a >> x;
            segtree.set(a - 1, x, k - 1);
        } else if (t == 2) {
            int k, a, b; cin >> k >> a >> b;
            cout << segtree.sum(a - 1, b, k - 1) << '\n';
        } else {
            int k; cin >> k;
            segtree.copy_array(k - 1);
        }
    }
}