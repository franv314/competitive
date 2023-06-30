#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

class Seg1D {
    struct Node {
        int val;
        int nb, ne;
        Node *lc, *rc;
    } *nodes, **roots;
    int n, r;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            nodes[n] = {0, nb, ne, NULL, NULL};
            return &nodes[n++];
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        nodes[n] = {lc->val + rc->val, nb, ne, lc, rc};
        return &nodes[n++];
    }

    Node* set(int x, int v, Node* node) {
        if (node->nb > x || node->ne <= x) return node;
        if (node->nb + 1 == node->ne) {
            nodes[n] = {v, node->nb, node->ne, NULL, NULL};
            return &nodes[n++];
        }
        Node *lc = set(x, v, node->lc);
        Node *rc = set(x, v, node->rc);
        nodes[n] = {lc->val + rc->val, node->nb, node->ne, lc, rc};
        return &nodes[n++];
    }

    int sum(int l, int r, Node* node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->val;
        return sum(l, r, node->lc) + sum(l, r, node->rc);
    }

public:

    int versions() { return r - 1; }

    void set(int x, int v) {
        roots[r] = set(x, v, roots[r - 1]);
        r++;
    }

    int sum(int l, int r, int v) {
        return sum(l, r, roots[v]);
    }

    Seg1D() { }
    Seg1D(int N) {
        n = 0, r = 0;
        nodes = (Node*)malloc(12'000'000 * sizeof(Node));
        roots = (Node**)malloc(600'001 * sizeof(Node*));
        roots[r++] = build(0, N);
    }
};

Seg1D tree;
int N;
int version[200'000];

void inizia(int N, int K, int V[], int R[]) {
    ::N = N;
    tree = Seg1D(N);
    vector<vector<int>> pos(K, vector<int>());

    for (int i = 0; i < N; i++) {
        pos[V[i]].push_back(i);
        int size = pos[V[i]].size();

        for (int j = min(size - 1, size - R[V[i]]); j >= max(0, size - R[V[i]] - 2); j--) {
            if (j == size - R[V[i]]) tree.set(pos[V[i]][size - R[V[i]]], R[V[i]]);
            else if (j == size - R[V[i]] - 1) tree.set(pos[V[i]][size - R[V[i]] - 1], -R[V[i]]);
            else if (j == size - R[V[i]] - 2) tree.set(pos[V[i]][size - R[V[i]] - 2], 0);
        }

        version[i] = tree.versions(); 
    }
}

int istiga(int i, int j) {
    return tree.sum(i, N, version[j]);
}