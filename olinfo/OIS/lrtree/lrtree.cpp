#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long w(long long b, int e) {
    long long ans = 1;
    for (; e; e >>= 1) {
        if (e & 1) ans = (ans * b) % MOD;
        b = (b * b) % MOD;
    }
    return ans;
}

int main() {
    int N; cin >> N;
    
    long long cat1 = 1;
    for (int k = 2; k <= N; k++) {
        cat1 = (cat1 * (N + k)) % MOD;
        cat1 = (cat1 * w(k, MOD - 2)) % MOD;
    }
    
    long long cat2 = 1;
    for (int k = 2; k <= N / 2; k++) {
        cat2 = (cat2 * (N / 2 + k)) % MOD;
        cat2 = (cat2 * w(k, MOD - 2)) % MOD;
    }

    cout << (N & 1 ? cat1 - cat2 + MOD : cat1) * w(2, MOD - 2) % MOD;
}