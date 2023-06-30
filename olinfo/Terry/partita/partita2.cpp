#include <bits/stdc++.h>
using namespace std;

class SegTree {
    struct Node {
        pair<int, int> val;
        int nb, ne;
        Node *lc, *rc;

        Node(pair<int, int> v, int b, int e, Node *l, Node *r) :
            val(v), nb(b), ne(e), lc(l), rc(r) { }
    } *root;

    Node *build(int nb, int ne, int arr[]) {
        if (nb + 1 == ne) return new Node({arr[nb], nb}, nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2, arr);
        Node *rc = build((nb + ne) / 2, ne, arr);
        return new Node(max(lc->val, rc->val), nb, ne, lc, rc);
    } 

    void update(int x, Node *node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->val.first = 0;
            return;
        }
        update(x, node->lc);
        update(x, node->rc);
        node->val = max(node->lc->val, node->rc->val);
    }

    pair<int, int> query(int l, int r, Node *node) {
        if (node->nb >= r || node->ne <= l) return {INT_MIN, 0};
        if (l <= node->nb && node->ne <= r) return node->val;
        
        return max(query(l, r, node->lc), query(l, r, node->rc));
    }

public:

    void update(int x) { update(x, root); }
    pair<int, int> query(int l, int r) { return query(l, r, root); }
    SegTree(vector<int> arr) {
        root = build(0, arr.size(), arr.data());
    }

};

void solve(int t) {
    int N;
    int K;
    cin >> N >> K;
    vector<int> R(N);
    for (int i = 0; i < N; i++) cin >> R[i];

    SegTree tree(R);

    int risposta = 0;
    int reachable = K;
    while (reachable <= N) {
        auto [ma, pos] = tree.query(0, reachable);
        if (ma == 0) {
            risposta = -1;
            break;
        }
        tree.update(pos);
        reachable += ma;
        risposta++;
    }

    cout << "Case #" << t << ": " << risposta << "\n";
}

int main() {
    // Se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
