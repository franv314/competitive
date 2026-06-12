#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr int MAXN = 2e6;
constexpr int MOD = 1e9 + 7;

i64 fact[MAXN + 1], invs[MAXN + 1];

i64 fexp(i64 b, i64 e) {
    i64 a = 1;
    do {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    } while (e >>= 1);
    return a;
}

i64 binom(i64 n, i64 k) {
    if (k > n || k < 0) return 0;
    return fact[n] * invs[k] % MOD * invs[n - k] % MOD;
}

i64 cat(i64 n) {
    return (binom(2 * n, n) - binom(2 * n, n + 1) + MOD) % MOD;
}

void precalc() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = i * (fact[i - 1]) % MOD;
    invs[MAXN] = fexp(fact[MAXN], MOD - 2);
    for (int i = MAXN - 1; i >= 0; i--)
        invs[i] = invs[i + 1] * (i + 1) % MOD;
}

void solve() {
    i64 n, k; cin >> n >> k;
    
    i64 ans = 0;

    for (int i = 0; i < 2 && k >= 0; i++) {
        vector<i64> pref_count(n + 1);
        pref_count[0] = 1;
        for (int i = 1; i <= k; i++)
            pref_count[i] = 2 * pref_count[i - 1] % MOD;
        
        for (int i = k + 1; i <= n; i++)
            pref_count[i] = (2 * pref_count[i - 1] - binom(i - 1, k) + MOD) % MOD;

        for (int left = 0; left <= n - 1; left++) {
            int right = n - 1 - left;

            i64 coeff = cat(left) * cat(right) % MOD;

            i64 count_maxl = binom(left, k) * pref_count[right] % MOD;
            i64 count_maxr = binom(right, k) * pref_count[left] % MOD;
            i64 count_maxb = binom(left, k) * binom(right, k) % MOD;

            i64 count = (count_maxl + count_maxr - count_maxb + MOD) % MOD;

            ans = (ans + count * coeff) % MOD;
        }
        
        k--;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    precalc();

    int t; cin >> t;
    while (t--) solve();
}
