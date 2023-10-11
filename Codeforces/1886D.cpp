#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;

struct SegTree {
    struct Node {
        long long val;
        int nb, ne;
        Node *lc, *rc;

        Node(int nb, int ne, Node *lc, Node *rc) :
            val(1), nb(nb), ne(ne), lc(lc), rc(rc) { }
    } *root;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(nb, ne, NULL, NULL);
        return new Node(nb, ne, build(nb, (nb + ne) / 2), build((nb + ne) / 2, ne));
    }

    void set(int x, int val, Node *node) {
        if (node->nb + 1 == node->ne) return void(node->val = val);
        if (x >= (node->nb + node->ne) / 2) set(x, val, node->rc);
        else set(x, val, node->lc);

        node->val = node->lc->val * node->rc->val % MOD;
    }

public:
    int query() { return root->val; }
    void set(int x, int val) { set(x, val, root); }

    SegTree(int size) { root = build(0, size); }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, M; cin >> N >> M;
    SegTree segtree(N - 1);

    string S; cin >> S;
    for (int i = 0; i < S.size(); i++) {
        segtree.set(i, S[i] == '?' ? i : 1);
    }

    cout << segtree.query() << '\n';
    while (M--) {
        int i; cin >> i;
        char c; cin >> c;

        segtree.set(i - 1, c == '?' ? i - 1 : 1);
        cout << segtree.query() << '\n';
    }
}