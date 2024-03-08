#include <bits/stdc++.h>
using namespace std;

struct Treap {
    char val;
    int pri;

    int size;
    Treap *lc, *rc;

    Treap(char val) : val(val), pri(rand()), size(1), lc(NULL), rc(NULL) { }
};

int size(Treap *treap) { return treap == NULL ? 0 : treap->size; }

void merge(Treap *left, Treap *right, Treap *&treap) {
    if (left == NULL) return void(treap = right);
    if (right == NULL) return void(treap = left);

    if (left->pri <= right->pri) {
        treap = left;
        merge(left->rc, right, left->rc);
    } else {
        treap = right;
        merge(left, right->lc, right->lc);
    }

    treap->size = 1 + size(treap->lc) + size(treap->rc);
}

void split(Treap *treap, Treap *&left, Treap *&right, int k) {
    if (treap == NULL) return void(left = right = NULL);

    if (k > size(treap->lc)) {
        left = treap;
        split(treap->rc, left->rc, right, k - 1 - size(treap->lc));
    } else {
        right = treap;
        split(treap->lc, left, right->lc, k);
    }

    treap->size = 1 + size(treap->lc) + size(treap->rc);
}

ostream& operator<<(ostream &out, Treap *treap) {
    if (treap == NULL) return out;
    return out << treap->lc << treap->val << treap->rc;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    string s; cin >> s;

    Treap *treap = NULL;
    for (auto c: s) merge(treap, new Treap(c), treap);

    while (m--) {
        int a, b; cin >> a >> b;
        a--;

        Treap *left, *mid, *right;
        split(treap, left, mid, a);
        split(mid, mid, right, b - a);
        merge(left, right, treap);
        merge(treap, mid, treap);
    }

    cout << treap << '\n';
}