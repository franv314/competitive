#include <bits/stdc++.h>
using namespace std;

#define MAXN 70'000

typedef uint64_t hash_t;

struct Hash {
    function<hash_t(hash_t, hash_t)> extend;
    function<hash_t(hash_t, hash_t, int)> pop;
    
    Hash(int b) {
        vector<int> powers(MAXN);
        powers[0] = 1;
        for (int i = 1; i < MAXN; i++) powers[i] = powers[i - 1] * b;
        
        extend = [=](hash_t h, hash_t c) {
            return h * b + c;
        };
        
        pop = [=](hash_t h, hash_t p, int l) {
            return h - p * powers[l];
        };
    }
} hasher(3);

class SegTree {
    struct Node {
        int ma, mi;
        int nb, ne;
        Node *lc, *rc;
    } *nodes, *root;
    int node;

    Node* build(int nb, int ne, int arr[]) {
        if (nb + 1 == ne) {
            nodes[node] = {arr[nb], arr[nb], nb, ne, NULL, NULL};
            return &nodes[node++];
        }
        Node *lc = build(nb, (nb + ne) / 2, arr);
        Node *rc = build((nb + ne) / 2, ne, arr);
        nodes[node] = {max(lc->ma, rc->ma), min(lc->mi, rc->mi), nb, ne, lc, rc};
        return &nodes[node++];
    }

    int upper_bound_right(int x, int d, Node* node) {
        if (node->ne <= x || node->ma < d) return -1;
        if (node->nb + 1 == node->ne) return node->nb;
        int l = upper_bound_right(x, d, node->lc);
        return l >= 0 ? l : upper_bound_right(x, d, node->rc);
    }

    int upper_bound_left(int x, int d, Node* node) {
        if (node->nb > x || node->mi > d) return -1;
        if (node->nb + 1 == node->ne) return node->nb;
        int l = upper_bound_left(x, d, node->rc);
        return l >= 0 ? l : upper_bound_left(x, d, node->lc);
    }

public:

    int upper_bound_right(int x, int d) {
        return upper_bound_right(x, d, root);
    }

    int upper_bound_left(int x, int d) {
        return upper_bound_left(x, d, root);
    }

    SegTree() { }
    SegTree(int N, int A[]) {
        node = 0;
        nodes = (Node*)malloc(3'000'000 * sizeof(Node));
        root = build(0, N, A);
    }

} tree_sx, tree_dx;

int N;
string S;

hash_t pref_hash_n[MAXN + 1], // [0, i)
       pref_hash_i[MAXN + 1], // [0, i)
       suff_hash_n[MAXN + 1], // [i, N)
       suff_hash_i[MAXN + 1]; // [i, N)

int i_dx[MAXN], i_sx[MAXN];
int max_antipalindrome[MAXN];

void find_antipalindromes() {
    for (int i = 0; i < N; i++) {
        int offset = 1;
        while (i - offset >= 0 && i + offset < N && S[i - offset] != S[i + offset]) offset++;
        max_antipalindrome[i] = offset - 1;
        
        i_sx[i] = i - max_antipalindrome[i];
        i_dx[i] = i + max_antipalindrome[i];
    }
    tree_sx = SegTree(N, i_sx);
    tree_dx = SegTree(N, i_dx);
}

void calculate_hash() {
    for (int i = 0; i < N; i++) {
        pref_hash_n[i + 1] = hasher.extend(pref_hash_n[i], S[i] == '1');
        pref_hash_i[i + 1] = hasher.extend(pref_hash_i[i], S[i] != '1');
    }
    
    for (int i = N - 1; i >= 0; i--) {
        suff_hash_n[i] = hasher.extend(suff_hash_n[i + 1], S[i] == '1');
        suff_hash_i[i] = hasher.extend(suff_hash_i[i + 1], S[i] != '1');
    }
}

int best = INT_MAX;

void recursive(int i, int j, int d = 0) {
    if (d >= best) return;
    if (j - i < 2) return void(best = min(best, d + j - i + 1));
    int x = tree_dx.upper_bound_right((i + j + 1) / 2, j);
    int y = tree_sx.upper_bound_left((i + j) / 2, i);

    if (x - i < j - y) {
        recursive(i, x - 1, d + 1);
        recursive(y + 1, j, d + 1);
    } else {
        recursive(y + 1, j, d + 1);
        recursive(i, x - 1, d + 1);
    }
}

int piega(int N, string S) {
    assert(N <= 20);
    ::N = N, ::S = S;
    
    find_antipalindromes();
    calculate_hash();
    
    recursive(0, N - 1);
    return best;
}