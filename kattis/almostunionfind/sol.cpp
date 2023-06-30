#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'001

struct Node {
    int size;
    long long sum;
    Node *next;
};

Node* elems[MAXN];

Node* find(Node *node) {
    if (node->next == NULL) return node;
    return node->next = find(node->next);
}

void merge(Node *u, Node *v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (u->size < v->size) swap(u, v);

    u->size += v->size;
    u->sum += v->sum;
    v->next = u;
}

void move(int val, int dest) {
    Node *ref_dest = find(elems[dest]);
    Node *ref = find(elems[val]);

    if (ref == ref_dest) return;

    ref->size--;
    ref->sum -= val;

    ref_dest->size++;
    ref_dest->sum += val;
    elems[val] = new Node({0, 0, ref_dest});
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            elems[i] = new Node({1, i, NULL});
        }

        while (m--) {
            int t; cin >> t;
            if (t == 1) {
                int p, q; cin >> p >> q;
                merge(elems[p], elems[q]);
            } else if (t == 2) {
                int p, q; cin >> p >> q;
                move(p, q);
            } else {
                int p; cin >> p;
                Node *ref = find(elems[p]);
                cout << ref->size << " " << ref->sum << "\n"; 
            }
        }
    }
}