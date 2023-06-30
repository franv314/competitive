#include <bits/stdc++.h>
using namespace std;

class Seg1D {
    struct Node {
        int first, last;
        long long total;

        int nb, ne;
        Node *lc, *rc;

        Node(int f, int l, long long t, int b, int e, Node *_1, Node *_2) :
            first(f), last(l), total(t), nb(b), ne(e), lc(_1), rc(_2) { }
    } *root;

    long long find_tot(Node *node, int threshold) {
        if (node->nb + 1 == node->ne) {
            return node->total * (node->first > threshold);
        }
        if (node->rc->first > threshold) {
            return node->total - node->rc->total + find_tot(node->rc, threshold);
        }
        return find_tot(node->lc, threshold);
    }

    Node* build(int nb, int ne, int* S) {
        if (nb + 1 == ne) {
            return new Node(S[nb], S[nb], S[nb], nb, ne, NULL, NULL);
        }
        Node* lc = build(nb, (nb + ne) / 2, S);
        Node* rc = build((nb + ne) / 2, ne, S);

        int last = rc->last;
        int first = max(lc->first, rc->first);
        long long total = rc->total + find_tot(lc, rc->first);

        return new Node(first, last, total, nb, ne, lc, rc);
    }

    void set(int x, int v, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->first = node->last = node->total = v;
            return;
        }
        set(x, v, node->lc);
        set(x, v, node->rc);

        node->last = node->rc->last;
        node->first = max(node->lc->first, node->rc->first);
        node->total = node->rc->total + find_tot(node->lc, node->rc->first);
    }

public:

    void set(int x, int v) { set(x, v, root); }
    long long query() { return root->total; }

    Seg1D(vector<int> S) {
        root = build(0, S.size(), S.data());
    }

};

int main() {
    int N, Q; cin >> N >> Q;
    vector<int> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    Seg1D tree(S);

    for (int i = 0; i < Q; i++) {
        int p, s; cin >> p >> s;
        tree.set(p, s);
        cout << tree.query() << endl;
    }
}