#include <bits/stdc++.h>
using namespace std;

bool chiedi(int K);
void stato();
void sposta();

struct Range {
    int lo, hi;
};

int pos = 0, dir = 1;

void move_to(int P) {
    if (dir * (P - pos) < 0) {
        stato();
        dir *= -1;
    }
    for (; pos != P; pos += dir)
        sposta();
}

void parallel_binary_search(int N, int H[]) {
    iota(&H[0], &H[N], 0);
    vector<Range> ranges = {{0, N - 1}};
    
    int iters = ceil(log2(N));
    for (int i = 0; i < iters; i++) {
        vector<Range> new_ranges = {};

        for (auto it = ranges.rbegin(); it != ranges.rend(); it++) {
            Range range = *it;
            int m = (range.lo + range.hi) / 2;
            move_to(m);

            int p = range.hi;
            for (int i = range.lo; i <= p; i++) {
                if (!chiedi(H[i])) {
                    swap(H[i--], H[p--]);
                }
            }
            if (i & 1) {
                new_ranges.push_back({range.lo, m});
                new_ranges.push_back({m + 1, range.hi});
            } else {
                new_ranges.push_back({m + 1, range.hi});
                new_ranges.push_back({range.lo, m});
            }
        }
        ranges = new_ranges;
    }
}

void _40_25_search(int N, int H[]) {
    iota(&H[0], &H[N], 0);

    for (int i = 24; i < N - 25; i += 25) {
        move_to(i);

        int k = i - 24;
        for (int j = i - 24; j < N; j++) {
            if (chiedi(H[j])) {
                swap(H[j], H[k++]);
            }
        }
    }
    for (int i = N - 2; i >= 0; i--) {
        move_to(i);
        for (int j = i; j >= 25 * (i / 25); j--) {
            if (!chiedi(H[j])) {
                swap(H[i + 1], H[j]);
                break;
            }
        }
    }
}

void indovina(int N, int A, int B, int C, int H[]) {
    if (B > 1) parallel_binary_search(N, H);
    else _40_25_search(N, H);
}