#include <bits/stdc++.h>
using namespace std;

#define MAXN 1'000'000

constexpr int MOD = 1e9 + 7;
vector<int> fact;
vector<int> invs;

int fexp(int base, int exp) {
    int ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (long long)ans * base % MOD;
        base = (long long)base * base % MOD;
    }
    return ans;
}

void precalc() {
    fact.resize(2 * MAXN + 1);
    invs.resize(2 * MAXN + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= 2 * MAXN; i++) {
        fact[i] = (long long)i * fact[i - 1] % MOD;
    }

    invs[2 * MAXN] = fexp(fact[2 * MAXN], MOD - 2);
    for (int i = 2 * MAXN - 1; i >= 0; i--) {
        invs[i] = (long long)(i + 1) * invs[i + 1] % MOD;
    }
}

int binom(int n, int m) {
    if (m < 0 || m > n) return 0;
    return (long long)fact[n] * invs[m] % MOD * invs[n - m] % MOD;
}

int main() {
    int N; cin >> N;
    
    precalc();

    int ans = 1;
    int curr_val = 1;
    
    for (int k = 1; k <= N; k++) {
        curr_val = curr_val * 2 % MOD;
        ans = (ans + curr_val) % MOD;
    }

    for (int k = N + 1; k <= 2 * N; k++) {
        curr_val = (curr_val * 2) % MOD;
        curr_val = (curr_val - 2LL * binom(k, k - N - 1) + 2LL * MOD) % MOD;
        curr_val = (curr_val + 2LL * binom(k - 1, k - N - 2)) % MOD;
        ans = (ans + curr_val) % MOD;
    }

    cout << ans << '\n';
}