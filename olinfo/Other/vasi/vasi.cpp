#include <bits/stdc++.h>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct Node {
    Node *left, *right;
    int weight, size, value;

    Node() {}

    Node(int v) {
        left = right = NULL;
        weight = rand();
        size = 1;
        value = v;
    }
};

Node nodes[10'000'000];

int size(Node *treap) {
    if (treap == NULL) return 0;
    return treap->size;
}

void split(Node *treap, Node *&left, Node *&right, int k) {
    if (treap == NULL) {
        left = right = NULL;
        return;
    }
    if (size(treap->left) < k) {
        split(treap->right, treap->right, right, k - size(treap->left) - 1);
        left = treap;
    } else {
        split(treap->left, left, treap->left, k);
        right = treap;
    }
    treap->size = size(treap->left) + size(treap->right) + 1;
}

void merge(Node *&treap, Node *left, Node *right) {
    if (left == NULL) treap = right;
    else if (right == NULL) treap = left;
    else {
        if (left->weight < right->weight) {
        merge(left->right, left->right, right);
        treap = left;
        } else {
            merge(right->left, left, right->left);
            treap = right;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

int get_val(Node *treap, int pos) {
    if (pos == size(treap->left)) return treap->value;
    if (pos < size(treap->left)) return get_val(treap->left, pos);
    return get_val(treap->right, pos - size(treap->left) - 1);
}

int main() {
    int N, M; in >> N >> M;
    
    Node *treap = NULL;
    for (int t = 0; t < N; t++) {
        nodes[t] = Node(t);
        merge(treap, treap, &nodes[t]);
    }

    char c;
    int i, j;
    while (M--) {
        in >> c;
        if (c == 's') {
            in >> i >> j;
            Node *left, *center, *right, *elem;
            if (i < j) {
                split(treap, left, treap, i);
                split(treap, elem, treap, 1);
                split(treap, center, right, j - i);

                merge(treap, left, center);
                merge(treap, treap, elem);
                merge(treap, treap, right);
            } else {
                split(treap, left, treap, j);
                split(treap, center, treap, i - j);
                split(treap, elem, right, 1);

                merge(treap, left, elem);
                merge(treap, treap, center);
                merge(treap, treap, right);
            }
        } else {
            in >> i;
            out << get_val(treap, i) << " ";
        }
    }
}