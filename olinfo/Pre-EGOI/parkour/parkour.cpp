#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define MAXN 1000000

class Seg1D {
    int *min_tree;
    int size;

    void update() {
        for (int i = size / 2 - 1; i > 0; i--)
            min_tree[i] = min(min_tree[2 * i], min_tree[2 * i + 1]);
    }

public:

    int get_min(int L, int R) {
        int res = 1e9;
        for (int l = L + size / 2, r = R + size / 2; l < r; l /= 2, r /= 2) {
            if (l & 1) res = min(res, min_tree[l++]);
            if (r & 1) res = min(res, min_tree[--r]);
        }
        return res;
    }

    void set_pos(int P, int x) {
        int p = P + size / 2;
        min_tree[p] = x;
        for (p /= 2; p > 0; p /= 2) {
            if (min_tree[p] == min(min_tree[2 * p], min_tree[2 * p + 1])) return;
            min_tree[p] = min(min_tree[2 * p], min_tree[2 * p + 1]);
        }
    }

    int operator[](int pos) {
        return min_tree[pos + size / 2];
    }

    Seg1D(int N) {
        size = 2 << (int) ceil(log2(N));
        min_tree = (int*) malloc(size * sizeof(int));

        min_tree[N + size / 2] = 0;
        update();
    }
};

int salta(int N, vector<int> S, vector<int> A, vector<int> B) {
    S.push_back(0);

    Seg1D memo(N + 1);

    for (int i = N - 1; i >= 0; i--) {
        int opt = memo.get_min(i + A[i], i + B[i] + 1);
        memo.set_pos(i, max(opt, S[i]));
    }
    return memo[0];
}