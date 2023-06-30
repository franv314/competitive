#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

int connected(int d, int max) {
    if (d == 0) return 1;

    int connected_size = 1;
    while (!(d & connected_size)) connected_size <<= 1;

    int done = 0;
    int total = 0;
    for (int curr = 1 << 30; curr && !(done & d); curr >>= 1) {
        if (!(max & curr)) continue;

        int count = 1;
        for (int c = connected_size; c < curr; c <<= 1)
            if (!(c & d))
                count *= 2;

        total += count - (done && !(d & done) && !(d & done - 1));
        done |= curr;
    }

    return total;
}

vector<int> conta(int N, int M, int Q, vector<int> A, vector<int> B, vector<int> C, vector<int> D) {
    vector<int> res(Q);
    for (int i = 0; i < Q; i++) {
        int conn_1 = connected(A[i], D[i] + 1) - connected(A[i], B[i]) + (!(A[i] & B[i]) && !(A[i] & B[i] - 1));
        int conn_2 = connected(B[i], C[i] + 1) - connected(B[i], A[i]) + (!(B[i] & A[i]) && !(B[i] & A[i] - 1));

        res[i] = conn_1 + conn_2 - !(A[i] & B[i]);
    }
    return res;
}