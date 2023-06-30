#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000
#define _ << " " <<

struct Node {
    int nb, ne;
    int val;

    Node *lc, *rc;
};

class Seg1D {
    Node *tree, **roots;
    int nodes, ver;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            tree[nodes] = {nb, ne, 0, NULL, NULL};
            return &tree[nodes++];
        }
        Node* lc = build(nb, (nb + ne) / 2);
        Node* rc = build((nb + ne) / 2, ne);
        tree[nodes] = {nb, ne, 0, lc, rc};
        return &tree[nodes++];
    }

    Node* set(int x, int v, Node* node) {
        if (x < node->nb || x >= node->ne) return node;
        if (node->nb + 1 == node->ne) {
            tree[nodes] = {node->nb, node->ne, v, NULL, NULL};
            return &tree[nodes++];
        }
        Node *lc = set(x, v, node->lc);
        Node *rc = set(x, v, node->rc);
        tree[nodes] = {node->nb, node->ne, lc->val + rc->val, lc, rc};
        return &tree[nodes++];
    }

    int sum(int l, int r, Node* node) {
        if (r <= node->nb || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return sum(l, r, node->lc) + sum(l, r, node->rc);
    }

public:

    int sum(int l, int r, int version) {
        return sum(l, r, roots[version]);
    }

    void set(int x, int v) {
        roots[ver] = set(x, v, roots[ver - 1]);
        ver++;
    }

    Seg1D () { }
    Seg1D (int n) {
        nodes = 0, ver = 0;
        tree = (Node*)malloc(2000000 * sizeof(Node));
        roots = (Node**)malloc(200001 * sizeof(Node**));

        roots[ver++] = build(0, n);
    }
};

Seg1D segtree;
int curr, updates, versions[MAXN + 1];
int n;

void init(int n) {
    ::n = n;
	segtree = Seg1D(n);
}

void log(vector<int>& added, vector<int>& removed) {
	for (auto x: added) {
        updates++;
        segtree.set(x, 1);
    }
    for (auto x: removed) {
        updates++;
        segtree.set(x, 0);
    }
    versions[++curr] = updates;
}

int answer(int d, int x) {
	return segtree.sum(x, n, versions[d]);
}