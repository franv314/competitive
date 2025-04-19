#include "thief.h"
#include <bits/stdc++.h>
using namespace std;

void solve_dir(int N) {
    int l = 0, r = N - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        vector<int> q(N - 1, 1);
        fill(q.begin(), q.begin() + m, 0);
        
        if (query(q)) r = m;
        else l = m;
    }

    answer(0, r);
}

void solve_inv(int N) {
    int l = 0, r = N - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        vector<int> q(N - 1, 0);
        fill(q.begin(), q.begin() + m, 1);
        
        if (query(q)) r = m;
        else l = m;
    }

    answer(r, 0);
}

void solve_bad(int N) {
    assert(false);
}

void solve_mix(int N) {
    int l = 0, r = N;
    while (r - l > 1) {
        int m = (l + r) / 2;
        vector<int> q(N - 1, 0);
        fill(q.begin(), q.begin() + m, 1);

        if (query(q)) r = m;
        else l = m;
    }

    if (r == N) return solve_bad(N);

    int A = r;

    l = r, r = N;
    while (r - l > 1) {
        int m = (l + r) / 2;
        vector<int> q(N - 1, 0);
        fill(q.begin(), q.begin() + m, 1);

        if (query(q)) l = m;
        else r = m;
    }

    int B = r;

    answer(A, B);
}

void solve(int N, int M, vector<int> U, vector<int> V) {
    vector<int> q0(M, 0), q1(M, 1);
    if (query(q0)) {
        solve_dir(N);
    } else if (query(q1)) {
        solve_inv(N);
    } else {
        solve_mix(N);
    }
}
