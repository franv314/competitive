#include <bits/stdc++.h>
using namespace std;

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

int main() {
    populate_inverses();
    for (int i = 1; i < MOD; i++)
        cout << inverses[i] << ",\n";
}