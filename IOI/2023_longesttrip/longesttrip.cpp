#include <bits/stdc++.h>
#include "longesttrip.h"
using namespace std;

struct XorList {
    struct Node {
        int val;
        Node *x, *y;

        Node(int val) : val(val), x(NULL), y(NULL) { }
    } *start, *end;

    void merge(XorList *o) {
        if (end->x == NULL) {
            end->x = o->start;
        } else {
            end->y = o->start;
        }

        if (o->start->x == NULL) {
            o->start->x = end;
        } else {
            o->start->y = end;
        }

        end = o->end;
        o->start = o->end = NULL;
    }

    vector<int> vectorize() {
        vector<int> ans;
        
        Node* curr = start, *old = NULL;
        while (curr != NULL) {
            ans.push_back(curr->val);

            if (old == curr->x) {
                old = curr;
                curr = old->y;
            } else {
                old = curr;
                curr = old->x;
            }
        }
        return ans;
    }

    int first() { return start->val; }
    int last() { return end->val; }
    void reverse() { swap(start, end); }
    XorList(int val) { start = end = new Node(val); }
};

vector<int> longest_trip(int N, int D) {
    XorList *a = new XorList(0);
    XorList *b = new XorList(1);
    
    for (int i = 2; i < N; i++) {
        int last_a = a->last();
        int last_b = b->last();
        XorList *m = new XorList(i);

        if (are_connected({last_a}, {last_b})) {
            b->reverse();
            a->merge(b);

            b = m;
        } else if (are_connected({last_a}, {i})) {
            a->merge(m);
        } else {
            b->merge(m);
        }
    }

    if (are_connected({a->first()}, {b->first()})) {
        a->reverse();
        a->merge(b);
        return a->vectorize();
    }

    if (are_connected({a->first()}, {b->last()})) {
        a->reverse();
        b->reverse();
        a->merge(b);
        return a->vectorize();
    }

    if (are_connected({a->last()}, {b->first()})) {
        a->merge(b);
        return a->vectorize();
    }

    if (are_connected({a->last()}, {b->last()})) {
        b->reverse();
        a->merge(b);
        return a->vectorize();
    }

    vector<int> chain_a = a->vectorize();
    vector<int> chain_b = b->vectorize();

    if (!are_connected(chain_a, chain_b)) {
        return chain_a.size() > chain_b.size() ? chain_a : chain_b;
    }

    int l1 = 0, r1 = chain_a.size();
    while (l1 + 1 < r1) {
        int m = (l1 + r1) / 2;
        if (are_connected(vector<int>(chain_a.begin() + m, chain_a.end()), chain_b)) {
            l1 = m;
        } else {
            r1 = m;
        }
    }

    int l2 = 0, r2 = chain_b.size();
    while (l2 + 1 < r2) {
        int m = (l2 + r2) / 2;
        if (are_connected(vector<int>(chain_b.begin() + m, chain_b.end()), {chain_a[l1]})) {
            l2 = m;
        } else {
            r2 = m;
        }
    }

    rotate(chain_a.begin(), chain_a.begin() + l1 + 1, chain_a.end());
    rotate(chain_b.begin(), chain_b.begin() + l2, chain_b.end());
    copy(chain_b.begin(), chain_b.end(), back_inserter(chain_a));

    return chain_a;
}
