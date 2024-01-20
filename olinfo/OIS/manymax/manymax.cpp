#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int fexp(int b, int e) {
    int ans = 1;
    for (; e; e >>= 1) {
        if (e & 1) ans = (long long)ans * b % MOD;
        b = (long long)b * b % MOD;
    }

    return ans;
}

class SegTree {
    struct Node {
        int cnt, prod;
        int nb, ne;
        Node *lc, *rc;

        Node(int cnt, int prod, int nb, int ne, Node *lc, Node *rc) :
            cnt(cnt), prod(prod), nb(nb), ne(ne), lc(lc), rc(rc) { }
    };
    vector<Node*> roots;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(0, 1, nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return new Node(0, 1, nb, ne, lc, rc);
    }

    Node* insert(int pos, int val, Node *node) {
        if (pos >= node->ne || pos < node->nb) return node;
        if (node->nb + 1 == node->ne) return new Node(1, val, node->nb, node->ne, NULL, NULL);

        if (pos < (node->nb + node->ne) / 2) {
            Node *lc = insert(pos, val, node->lc);
            Node *rc = node->rc;
            return new Node(lc->cnt + rc->cnt, (long long)lc->prod * rc->prod % MOD, node->nb, node->ne, lc, rc);
        } else {
            Node *lc = node->lc;
            Node *rc = insert(pos, val, node->rc);
            return new Node(lc->cnt + rc->cnt, (long long)lc->prod * rc->prod % MOD, node->nb, node->ne, lc, rc);
        }
    }

    pair<int, int> kth_product(int k, Node *node1, Node *node2) {
        if (node1->nb + 1 == node1->ne) return {node1->prod, node2->prod};

        int lcnt = node2->lc->cnt - node1->lc->cnt;
        if (lcnt >= k) return kth_product(k, node1->lc, node2->lc);

        auto [p1, p2] = kth_product(k - lcnt, node1->rc, node2->rc);
        return {(long long)p1 * node1->lc->prod % MOD, (long long)p2 * node2->lc->prod % MOD};
    }

public:

    void insert(int pos, int val) { roots.push_back(insert(pos, val, roots.back())); }
    pair<int, int> kth_product(int k, int l, int r) { return kth_product(k, roots[l], roots[r]); }
    SegTree(int N) { roots.push_back(build(0, N)); }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, Q; cin >> N >> Q;
    vector<int> V(N);

    for (auto &v: V) cin >> v;

    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return V[a] > V[b]; });

    vector<int> pos_of(N);
    for (int i = 0; i < N; i++) pos_of[order[i]] = i;

    SegTree segtree(N);
    for (int i = 0; i < N; i++) {
        segtree.insert(pos_of[i], V[i]);
    }

    while (Q--) {
        int L, R, K; cin >> L >> R >> K;

        auto [p1, p2] = segtree.kth_product(K, L, R + 1);
        int ans = (long long)p2 * fexp(p1, MOD - 2) % MOD;
        cout << ans << '\n';
    }
}