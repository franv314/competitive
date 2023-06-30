#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long value, lazy;
    int nb, ne;
    Node *lc, *rc;

    bool fully_outside(int l, int r) {
        return nb >= r || ne <= l;
    }

    bool fully_inside(int l, int r) {
        return l <= nb && ne <= r;
    }

    bool is_leaf() {
        return nb + 1 == ne;
    }
};

class Seg1D {
    Node *nodes, **roots;
    int pos, ver;

    Node* seg_build(int *A, int nb, int ne) {
        if (nb + 1 == ne) {
            nodes[pos] = {A[nb], 0, nb, ne, NULL, NULL};
            return &nodes[pos++];
        }
        Node* lc = seg_build(A, nb, (nb + ne) / 2);
        Node* rc = seg_build(A, (nb + ne) / 2, ne);
        nodes[pos] = {lc->value + rc->value, 0, nb, ne, lc, rc};
        return &nodes[pos++];
    }

    Node* dup_node(Node* node) {
        nodes[pos] = *node;
        return &nodes[pos++];
    }

    void update(Node* node) {
        if (node->lazy) {
            node->value += node->lazy * (node->ne - node->nb);
            if (!node->is_leaf()) {
                node->lc = dup_node(node->lc);
                node->rc = dup_node(node->rc);
                node->lc->lazy += node->lazy;
                node->rc->lazy += node->lazy;
            }
            node->lazy = 0;
        }
    }

    long long somma(int l, int r, Node* node) {
        update(node);
        if (node->fully_outside(l, r)) return 0;
        if (node->fully_inside(l, r)) return node->value;
        return somma(l, r, node->lc) + somma(l, r, node->rc);
    }

    Node* increment(int l, int r, int x, Node* node) {
        update(node);
        if (node->fully_outside(l, r)) return node;
        if (node->fully_inside(l, r)) {
            Node* new_node = dup_node(node);
            new_node->value += (long long) x * (node->ne - node->nb);
            if (!node->is_leaf()) {
                new_node->lc = dup_node(new_node->lc);
                new_node->rc = dup_node(new_node->rc);
                new_node->lc->lazy += x;
                new_node->rc->lazy += x;
            }
            return new_node;
        }
        Node* lc = increment(l, r, x, node->lc);
        Node* rc = increment(l, r, x, node->rc);
        nodes[pos] = {lc->value + rc->value, 0, node->nb, node->ne, lc, rc};
        return &nodes[pos++];
    }

    Node* resetta(int l, int r, int v, Node* curr_node, Node* reset_node) {
        update(curr_node);
        update(reset_node);
        if (curr_node->fully_outside(l, r)) return curr_node;
        if (curr_node->fully_inside(l, r)) return reset_node;
        Node* lc = resetta(l, r, v, curr_node->lc, reset_node->lc);
        Node* rc = resetta(l, r, v, curr_node->rc, reset_node->rc);
        nodes[pos] = {lc->value + rc->value, 0, curr_node->nb, curr_node->ne, lc, rc};
        return &nodes[pos++];
    }

public:

    long long somma(int l, int r) {
        return somma(l, r, roots[ver]);
    }

    void increment(int l, int r, int x) {
        roots[ver + 1] = increment(l, r, x, roots[ver]);
        ver++;
    }

    void resetta(int l, int r, int v) {
        roots[ver + 1] = resetta(l, r, v, roots[ver], roots[v]);
        ver++;
    }

    Seg1D(int N, int *A) {
        nodes = (Node*) malloc(15000000 * sizeof(Node));
        roots = (Node**) malloc(100000 * sizeof(Node*));
        pos = ver = 0;
        
        roots[0] = seg_build(A, 0, N);
    }

    Seg1D() { }
};

Seg1D git;

void inizia(int N, vector<int> A) {
    git = Seg1D(N, A.data());
}

void incrementa(int l, int r, int x) {
    git.increment(l, r, x);
}

void resetta(int l, int r, int v) {
    git.resetta(l, r, v);
}

long long somma(int l, int r) {
    return git.somma(l, r);
}