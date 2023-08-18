#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
//using namespace std;

class SegTree {

    int size;
    long long *sum_tree;
    long long *min_tree;
    std::pair<long long, bool> *lazy;

    void update() {
        for (int i = size / 2 - 1; i > 0; i--) {
            sum_tree[i] = sum_tree[2 * i] + sum_tree[2 * i + 1];
            min_tree[i] = std::min(min_tree[2 * i], min_tree[2 * i + 1]);
        }
    }

    void update(int N, int NB, int NE) {
        if (lazy[N].second) {
            sum_tree[N] = (NE - NB) * lazy[N].first;
            min_tree[N] = lazy[N].first;
            if (NB + 1 != NE)
                lazy[2 * N] = lazy[2 * N + 1] = lazy[N];
            lazy[N] = {0, false};
            return;
        }
        if (lazy[N].first) {
            sum_tree[N] += (NE - NB) * lazy[N].first;
            min_tree[N] += lazy[N].first;
            if (NB + 1 != NE) {
                lazy[2 * N].first += lazy[N].first;
                lazy[2 * N + 1].first += lazy[N].first;
            }
            lazy[N] = {0, false};
            return;
        }
    }

    void add(int L, int R, long long diff, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L) return; // OUTSIDE
        if (L <= NB && NE <= R) { // FULLY CONTAINED
            sum_tree[N] += (NE - NB) * diff;
            min_tree[N] += diff;
            if (NB + 1 != NE) {
                lazy[2 * N].first += diff;
                lazy[2 * N + 1].first += diff;
            }
            return;
        }
        if (NB + 1 == NE) {
            sum_tree[N] += diff;
            min_tree[N] += diff;
        } else {
            add(L, R, diff, 2 * N, NB, (NB + NE) / 2);
            add(L, R, diff, 2 * N + 1, (NB + NE) / 2, NE);
            sum_tree[N] = sum_tree[2 * N] + sum_tree[2 * N + 1];
            min_tree[N] = std::min(min_tree[2 * N], min_tree[2 * N + 1]);
        }
    }

    void set_range(int L, int R, long long val, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L) return; // OUTSIDE
        if (L <= NB && NE <= R) { // FULLY CONTAINED
            sum_tree[N] = (NE - NB) * val;
            min_tree[N] = val;
            if (NB + 1 != NE)
                lazy[2 * N] = lazy[2 * N + 1] = {val, true};
            return;
        }
        if (NB + 1 == NE) {
            sum_tree[N] = val;
            min_tree[N] = val;
        } else {
            set_range(L, R, val, 2 * N, NB, (NB + NE) / 2);
            set_range(L, R, val, 2 * N + 1, (NB + NE) / 2, NE);
            sum_tree[N] = sum_tree[2 * N] + sum_tree[2 * N + 1];
            min_tree[N] = std::min(min_tree[2 * N], min_tree[2 * N + 1]);
        }
    }

    long long get_sum(int L, int R, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L) return 0; // OUTSIDE
        if (L <= NB && NE <= R) // FULLY CONTAINED
            return sum_tree[N];
        return get_sum(L, R, 2 * N, NB, (NB + NE) / 2) +
               get_sum(L, R, 2 * N + 1, (NB + NE) / 2, NE);
    }

    long long get_min(int L, int R, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L) return 1e18; // OUTSIDE
        if (L <= NB && NE <= R) // FULLY CONTAINED
            return min_tree[N];
        return std::min(
            get_min(L, R, 2 * N, NB, (NB + NE) / 2),
            get_min(L, R, 2 * N + 1, (NB + NE) / 2, NE)
        );
    }

    int lower_bound(int L, int R, long long x, int N, int NB, int NE) {
        update(N, NB, NE);
        if (NB >= R || NE <= L || min_tree[N] > x) return -1; // OUTSIDE or TOO BIG
        if (NB + 1 == NE) // FULLY CONTAINED
            return NB;
        int low = lower_bound(L, R, x, 2 * N, NB, (NB + NE) / 2);
        return low != -1 ? low : lower_bound(L, R, x, 2 * N + 1, (NB + NE) / 2, NE);
    }

public:

    void set_range(int L, int R, long long val) {
        set_range(L, R, val, 1, 0, size / 2);
    }

    void add(int L, int R, long long diff) {
        add(L, R, diff, 1, 0, size / 2);
    }

    long long get_sum(int L, int R) {
        return get_sum(L, R, 1, 0, size / 2);
    }

    long long get_min(int L, int R) {
        return get_min(L, R, 1, 0, size / 2);
    }

    int lower_bound(int L, int R, long long x) {
        return lower_bound(L, R, x, 1, 0, size / 2);
    }

    SegTree(int N, long long A[]) {
        size = 2 << (int) ceil(log2(N));
        sum_tree = (long long*) calloc(size, sizeof(long long));
        min_tree = (long long*) calloc(size, sizeof(long long));
        lazy = (std::pair<long long, bool>*) calloc(size, sizeof(std::pair<long long, bool>));

        for (int i = 0; i < N; i++)
            sum_tree[i + size / 2] = min_tree[i + size / 2] = A[i];

        update();
    }
    SegTree() {
        size = 0;
        sum_tree = NULL;
        min_tree = NULL;
        lazy = NULL;
    }
};

SegTree tree;

void init(std::vector<long long> a) {
    tree = SegTree(a.size(), a.data());
}

long long get_sum(int L, int R) {
    return tree.get_sum(L, R);
}

void add(int L, int R, long long x) {
    tree.add(L, R, x);
}

void set_range(int L, int R, long long x) {
    tree.set_range(L, R, x);
}

long long get_min(int L, int R) {
    return tree.get_min(L, R);
}

long long lower_bound(int L, int R, long long x) {
    return tree.lower_bound(L, R, x);
}