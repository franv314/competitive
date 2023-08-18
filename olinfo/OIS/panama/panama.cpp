#include <bits/stdc++.h>
using namespace std;

#define INF ((long long)1e18)
#define _ << " " <<

struct Node {
    long long sum, max_sub, max_pref, max_suff;
    int nb, ne;

    Node *lc, *rc;
};

class Tree {
    Node *tree, *root;
    int nodes;

    Node* build(int arr[], int nb, int ne) {
        if (nb + 1 == ne) {
            tree[nodes] = {arr[nb], max(0, arr[nb]), max(0, arr[nb]), max(0, arr[nb]), nb, ne, NULL, NULL};
            return &tree[nodes++];
        }
        Node *lc = build(arr, nb, (nb + ne) / 2);
        Node *rc = build(arr, (nb + ne) / 2, ne);
        tree[nodes] = {
            lc->sum + rc->sum,
            max({lc->max_sub, rc->max_sub, lc->max_suff + rc->max_pref}),
            max(lc->max_pref, lc->sum + rc->max_pref),
            max(lc->max_suff + rc->sum, rc->max_suff),
            nb, ne, lc, rc
        };
        return &tree[nodes++];
    }

    void change(int x, int y, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->sum = y;
            node->max_sub = node->max_pref = node->max_suff = y;
            return;
        }
        change(x, y, node->lc);
        change(x, y, node->rc);
        
        node->sum = node->lc->sum + node->rc->sum;
        node->max_pref = max(node->lc->max_pref, node->lc->sum + node->rc->max_pref);
        node->max_suff = max(node->lc->max_suff + node->rc->sum, node->rc->max_suff);
        node->max_sub = max({node->lc->max_sub, node->rc->max_sub, node->lc->max_suff + node->rc->max_pref});
    }

    Node query(int x, int y, Node* node) {
        if (node->nb >= y || node->ne <= x) {
            return {0, -INF, -INF, -INF, node->nb, node->ne, NULL, NULL};
        }
        if (x <= node->nb && node->ne <= y) {
            return *node;
        }

        Node lc = query(x, y, node->lc);
        Node rc = query(x, y, node->rc);

        return {
            lc.sum + rc.sum,
            max({lc.max_sub, rc.max_sub, lc.max_suff + rc.max_pref}),
            max(lc.max_pref, lc.sum + rc.max_pref),
            max(lc.max_suff + rc.sum, rc.max_suff),
            node->nb, node->ne, NULL, NULL
        };
    }

public:

    long long query(int x, int y) {
        return query(x, y, root).max_sub;
    }

    void change(int x, int y) {
        change(x, y, root);
    }

    Tree(vector<int> arr) {
        tree = (Node*)malloc(1000000 * sizeof(Node));
        nodes = 0;
        root = build(arr.data(), 0, arr.size());
    }

};

int N, Q;
vector<int> V1, V2;

int main() {
    cin >> N >> Q;
    V1.resize(N);
    V2.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> V1[i];
        if (i & 1) V1[i] *= -1;
        V2[i] = -V1[i];
    }

    Tree seg1(V1), seg2(V2);

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            if (a & 1) {
                seg1.change(a - 1, b);
                seg2.change(a - 1, -b);
            } else {
                seg1.change(a - 1, -b);
                seg2.change(a - 1, b);
            }
        } else {
            int l, r;
            cin >> l >> r;
            cout << max(seg1.query(l - 1, r), seg2.query(l - 1, r)) << endl;
        }
    }

    return 0;
}