#include <bits/stdc++.h>
using namespace std;

class SegTree {
    struct Node {
        long long val, lazy;
        int nb, ne;
        Node *lc, *rc;

        void update() {
            if (lazy) {
                val += (ne - nb) * lazy;
                if (nb + 1 != ne) {
                    lc->lazy += lazy;
                    rc->lazy += lazy;
                }
                lazy = 0;
            }
        }

        Node(long long val, int nb, int ne, Node *lc, Node *rc) :
            val(val), lazy(0), nb(nb), ne(ne), lc(lc), rc(rc) { }
    } *root;

    Node* build(int nb, int ne, int arr[]) {
        if (nb + 1 == ne) return new Node(arr[nb], nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2, arr);
        Node *rc = build((nb + ne) / 2, ne, arr);
        return new Node(lc->val + rc->val, nb, ne, lc, rc);
    }

    void add(int l, int r, int d, Node *node) {
        node->update();
        if (node->ne <= l || node->nb >= r) return;
        if (l <= node->nb && node->ne <= r) {
            node->lazy += d;
            node->update();
            return;
        }
        add(l, r, d, node->lc);
        add(l, r, d, node->rc);
        node->val = node->lc->val + node->rc->val;
    }

    long long query(int l, int r, Node *node) {
        node->update();
        if (node->ne <= l || node->nb >= r) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    void add(int l, int r, int d) { add(l, r, d, root); }
    long long query(int l, int r) { return query(l, r, root); }
    SegTree(vector<int> A) { root = build(0, A.size(), A.data()); }

};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, Q; cin >> N >> Q;
    
    vector<int> A(N);
    for (auto &a: A) cin >> a;
    
    map<int, int> freq;
    for (auto a: A) freq[a]++;

    vector<pair<int, int>> freqs;
    for (auto [val, f]: freq) freqs.push_back({f, val});
    sort(freqs.begin(), freqs.end());

    vector<int> B(N);
    int l = 0, r = N - 1;
    for (int i = 0; i < freqs.size(); i++) {
        for (int j = 0; j < freqs[i].first; j++) {
            if (i % 2) B[r--] = freqs.size() - i / 2;
            else B[l++] = i / 2 + 1;
        }
    }

    SegTree segtree(B);
    long long ans = 0;
    l = 1;
    for (int i = 0; i < N; i++) {
        if (B[i] != l) {
            assert(++l == B[i]);
            segtree.add(i, N, -1);
        }
        ans += segtree.query(i, N);
    }
    cout << ans << '\n';
}