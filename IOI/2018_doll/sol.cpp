#include <bits/stdc++.h>
#include "doll.h"
using namespace std;

#define MAXS 400'000

void create_circuit(int M, vector<int> A) {
    int N = A.size();

    vector<int> C(M + 1, -1), X(MAXS), Y(MAXS);
    int cnt = 0;

    auto get_idx = [&](int sw) {
        return abs(sw) - 1;
    };

    auto rec = [&](auto &&rec, int l, int r) {
        if ((1 << (int)ceil(log2(N + 1))) - r > N) return -1;
        if (r - l == 1) return 0;

        int node_idx = --cnt;

        int lc = rec(rec, l, (l + r + 1) / 2);
        int rc = rec(rec, (l + r + 1) / 2, r);
    
        X[get_idx(node_idx)] = lc;
        Y[get_idx(node_idx)] = rc;
        return node_idx;
    };

    rec(rec, 0, 1 << (int)ceil(log2(N + 1)));
    X.resize(abs(cnt));
    Y.resize(abs(cnt));

    vector<int> status(abs(cnt));
    for (int i = 0; i <= N; i++) {
        int curr = -1;
        for (;;) {
            status[get_idx(curr)] ^= 1;
            int next = status[get_idx(curr)] ? X[get_idx(curr)] : Y[get_idx(curr)];
            
            if (next == 0) {
                int sus = i == N ? 0 : A[i];
                if (status[get_idx(curr)]) X[get_idx(curr)] = sus;
                else Y[get_idx(curr)] = sus;

                break;
            }

            curr = next;
        }
    }

    answer(C, X, Y);
}
