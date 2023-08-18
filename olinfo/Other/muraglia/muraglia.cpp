#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

vector<int> heights;
int N;

class SegTree {
    struct Node {
        int ma;
        int nb, ne;
        Node *lc, *rc;
    } *nodes, *root;
    int node;

    Node* build(int nb, int ne, int arr[]) {
        if (nb + 1 == ne) {
            nodes[node] = {arr[nb], nb, ne, NULL, NULL};
            return &nodes[node++];
        }
        Node *lc = build(nb, (nb + ne) / 2, arr);
        Node *rc = build((nb + ne) / 2, ne, arr);
        nodes[node] = {max(lc->ma, rc->ma), nb, ne, lc, rc};
        return &nodes[node++];
    }

    void update(int x, int v, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->ma = v;
            return;
        }
        update(x, v, node->lc);
        update(x, v, node->rc);
        node->ma = max(node->lc->ma, node->rc->ma);
    }

    int upper_bound_right(int x, int d, Node* node) {
        if (node->ne <= x || node->ma < d) return -1;
        if (node->nb + 1 == node->ne) return node->nb;
        int l = upper_bound_right(x, d, node->lc);
        return l >= 0 ? l : upper_bound_right(x, d, node->rc);
    }

    int upper_bound_left(int x, int d, Node* node) {
        if (node->nb > x || node->ma < d) return -1;
        if (node->nb + 1 == node->ne) return node->nb;
        int l = upper_bound_left(x, d, node->rc);
        return l >= 0 ? l : upper_bound_left(x, d, node->lc);
    }

public:

    pair<int, int> query(int x) {
        int right = upper_bound_right(x + 1, heights[x] + 1, root);
        int left = upper_bound_left(x - 1, heights[x] + 1, root);
        return {left >= 0 ? left : 0, right >= 0 ? right : N - 1};
    }

    void update(int x, int v) {
        update(x, v, root);
    }

    SegTree() { }
    SegTree(vector<int> A) {
        node = 0;
        nodes = (Node*)malloc(3'000'000 * sizeof(Node));
        root = build(0, A.size(), A.data());
    }

};

SegTree tree;

pair<int, int> chiedi(int x) {
    return tree.query(x);
}

void cambia(int x, int h) {
    tree.update(x, h);
    heights[x] = h;
}

void inizializza(int N, vector<int> H) {
    ::N = N;
	tree = SegTree(H);
    heights = H;
}