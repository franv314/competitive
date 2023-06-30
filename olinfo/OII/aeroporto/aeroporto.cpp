#include <bits/stdc++.h>
using namespace std;

void pianifica(int R, int A[], int B[], int T[]) {
    int l = 0, r = B[R - 1] + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        
        bool can = true;
        int old_t = INT_MIN;
        
        for (int i = 0; i < R; i++) {
            int min_t = max(old_t + m, A[i]);
            if (min_t <= B[i]) {
                old_t = min_t;
            } else {
                can = false;
                break;
            }
        }

        if (can) l = m;
        else r = m;
    }

    int old_t = INT_MIN;
    for (int i = 0; i < R; i++) {
        int min_t = max(old_t + l, A[i]);
        T[i] = min_t;
        old_t = min_t;
    }
}