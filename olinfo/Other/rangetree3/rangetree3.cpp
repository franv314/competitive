#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define INF ((int)1e18)

ifstream in("input.txt");
ofstream out("output.txt");
bool is_query;
int N, M, x, y;
vector<int> A;

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
            tree[nodes] = {arr[nb], arr[nb], arr[nb], arr[nb], nb, ne, NULL, NULL};
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
        if (node->nb >= y || node->ne <= x) return {-INF, -INF, -INF, -INF, node->nb, node->ne, NULL, NULL};
        if (x <= node->nb && node->ne <= y) return *node;

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

int main() {
    in >> N;
    A.resize(N);

    for (int n = 0; n < N; n++)
        in >> A[n];
    
    Tree tree(A);

    in >> M;
    for (int m = 0; m < M; m++) {
        in >> is_query >> x >> y;
        if (is_query) {
            out << tree.query(x - 1, y) << "\n";
        } else {
            tree.change(x - 1, y);
        }
    }
}