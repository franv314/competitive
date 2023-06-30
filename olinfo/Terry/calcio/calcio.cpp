#include <bits/stdc++.h>
using namespace std;

struct Seg1D {
    struct Node {
        int val;
        int nb, ne;
        Node *lc, *rc;
    } *nodes, *root;
    int no;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            nodes[no] = {0, nb, ne, NULL, NULL};
            return &nodes[no++];
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        nodes[no] = {0, nb, ne, lc, rc};
        return &nodes[no++];
    }

    void set(int x, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->val++;
            return;
        }
        set(x, node->lc);
        set(x, node->rc);
        node->val = node->lc->val + node->rc->val;
    }

    int query(int l, int r, Node* node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    void add(int x) {
        set(x, root);
    }

    int query(int l, int r) {
        return query(l, r, root);
    }

    Seg1D(int N) {
        no = 0;
        nodes = (Node*)malloc(20'000 * sizeof(Node));
        root = build(0, N);
    }
};

class Seg2D {
    struct Node {
        Seg1D val;
        int nb, ne;
        Node *lc, *rc;
    } *nodes, *root;
    int no;

    Node* build(int nb, int ne, int size) {
        if (nb + 1 == ne) {
            nodes[no] = {Seg1D(size), nb, ne, NULL, NULL};
            return &nodes[no++];
        }
        Node *lc = build(nb, (nb + ne) / 2, size);
        Node *rc = build((nb + ne) / 2, ne, size);
        nodes[no] = {Seg1D(size), nb, ne, lc, rc};
        return &nodes[no++];
    }

    void set(int x, int y, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->val.add(y);
            return;
        }
        set(x, y, node->lc);
        set(x, y, node->rc);
        node->val.add(y);
    }

    int query(int l, int r, int t, int b, Node* node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->val.query(t, b);
        return query(l, r, t, b, node->lc) + query(l, r, t, b, node->rc);
    }

public:

    void add(int x, int y) {
        set(x, y, root);
    }

    int query(int l, int r, int t, int b) {
        return query(l, r, t, b, root);
    }

    Seg2D(int N, int M) {
        no = 0;
        nodes = (Node*)malloc(20'000 * sizeof(Node));
        root = build(0, N, M);
    }
};


void solve(int t) {
    int N, M, K, A, B;
    cin >> N >> M >> K >> A >> B;

    Seg2D trees(N, M);

    for (int i = 0; i < K; i++) {
        int X, Y; cin >> X >> Y;
        trees.add(X, Y);
    }

    int mi = INT_MAX;
    for (int n = 0; n <= N - A; n++) {
        for (int m = 0; m <= M - B; m++) {
            mi = min(mi, trees.query(n, n + A, m, m + B));
        }
    }

    // aggiungi codice...
    int risposta = mi;
    

    cout << "Case #" << t << ": " << risposta << "\n";
}

int main() {
    // se preferisci leggere e scrivere da file
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
