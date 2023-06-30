#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

const int MOD = 46337;
int inverses[MOD];

void euclid_extended(int a, int b, int *m, int *n) {
    if (a == 0) {
        *m = 0, *n = 1;
        return;
    }

    int m1, n1;
    euclid_extended(b % a, a, &m1, &n1);
    
    *m = n1 - (b / a) * m1;
    *n = m1;
}

void populate_inverses() {
    for (int i = 1; i < MOD; i++) {
        euclid_extended(i, MOD, &inverses[i], &inverses[0]);
        inverses[i] = (inverses[i] + MOD) % MOD; 
    }
}

int conta(int N, int K, vector<int>& V) {
    populate_inverses();
    vector<int> amounts(K, 0);
    
    int l = 0, r = 0, found = 0;
    for (; found < K && r < N; r++) {
        if (amounts[V[r]]++ == 0) {
            found++;
        }
    }
    for (; found == K; l++) {
        if (--amounts[V[l]] == 0) {
            found--;
        }
    }

    amounts[V[l - 1]]++;
    long long prod = 1;
    for (auto x: amounts)
        prod = (prod * x) % MOD;
    amounts[V[l - 1]]--;

    int mi = r - l;
    int ret = prod;

    for (; r != N;) {
        for (; found < K && r < N; r++) {
            if (amounts[V[r]]++ == 0) {
                found++;
            } else {
                prod = (prod * amounts[V[r]] * inverses[(amounts[V[r]] - 1)]) % MOD;
            }
        }
        
        for (; found == K; l++) {
            if (--amounts[V[l]] == 0) {
                found--;
            } else {
                prod = (prod * amounts[V[l]] * inverses[(amounts[V[l]] + 1)]) % MOD;
            }
        }

        if (r - l == mi) {
            ret = (ret + prod) % MOD;
        } else if (r - l < mi) {
            ret = prod;
            mi = r - l;
        }
    }
    return ret % MOD;
}