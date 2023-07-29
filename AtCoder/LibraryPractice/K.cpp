#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;

class SegTree {
    struct Node {
        long long val;
        struct Aff : pair<long long, long long> {
            Aff compose(const Aff &other) {
                return Aff((first * other.first) % MOD, (first * other.second + second) % MOD);
            }
            
            Aff(int a, int b) : pair(a, b) { }
            Aff() : Aff(1, 0) { }
        } lazy;
        int nb, ne;  
        Node *lc, *rc;
        
        void update() {
            if (lazy != Aff(1, 0)) {
                val = (val * lazy.first + (ne - nb) * lazy.second) % MOD;
                if (nb + 1 != ne) {
                    lc->lazy = lazy.compose(lc->lazy);
                    rc->lazy = lazy.compose(rc->lazy);
                }
                lazy = {1, 0};
            }
        }
        
        Node(int val, int nb, int ne, Node *lc, Node *rc)
            : val(val), lazy(), nb(nb), ne(ne), lc(lc), rc(rc) { }
    } *root;
    
    Node* build(int nb, int ne, int arr[]) {
        if (nb + 1 == ne) return new Node(arr[nb], nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2, arr);
        Node *rc = build((nb + ne) / 2, ne, arr);
        return new Node((lc->val + rc->val) % MOD, nb, ne, lc, rc);
    }
    
    void update(int l, int r, Node::Aff aff, Node *node) {
        node->update();
        if (node->ne <= l || node->nb >= r) return;
        if (l <= node->nb && node->ne <= r) {
            node->lazy = aff;
            node->update();
            return;
        }
        update(l, r, aff, node->lc);
        update(l, r, aff, node->rc);
        node->val = (node->lc->val + node->rc->val) % MOD;
    }
    
    int query(int l, int r, Node *node) {
        node->update();
        if (node->ne <= l || node->nb >= r) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return (query(l, r, node->lc) + query(l, r, node->rc)) % MOD;
    } 
    
public:

    void update(int l, int r, int b, int c) { update(l, r, Node::Aff(b, c), root); }
    int query(int l, int r) { return query(l, r, root); }
    SegTree(vector<int> arr) { root = build(0, arr.size(), arr.data()); }
};

int main() {
    int N, Q; cin >> N >> Q;
    vector<int> arr(N);
    for (auto &a: arr) cin >> a;
    
    SegTree segtree(arr);
    
    while (Q--) {
        int t; cin >> t;
        if (t == 0) {
            int l, r, b, c; cin >> l >> r >> b >> c;
            segtree.update(l, r, b, c);
        } else {
            int l, r; cin >> l >> r;
            cout << segtree.query(l, r) << "\n";
        }
    }
}