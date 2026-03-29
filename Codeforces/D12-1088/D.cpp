#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr i64 MOD = 1e9 + 7;
constexpr int MAXN = 1e5;
constexpr int MAXB = 29;

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

void precalc() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invs[MAXN] = fexp(fact[MAXN], MOD - 2);
    for (int i = MAXN - 1; i >= 0; i--)
        invs[i] = invs[i + 1] * (i + 1) % MOD;
}

void solve() {
    int n; cin >> n;
    vector<i64> a(n);
    for (auto &x: a) cin >> x;
    reverse(a.begin(), a.end());

    vector<int> freq(MAXB);
    for (int i = 0; i < n; i++) {
        int cnt = n - i;
        for (int b = 0; b < MAXB; b++) {
            i64 contrib = (1LL << b) * binom(freq[b], cnt) % MOD;
            a[i] = (a[i] - contrib + MOD) % MOD;
        }
        for (int b = 0; b < MAXB; b++) {
            if (a[i] & (1 << b)) {
                freq[b] = cnt;
            }
        }
    }

    vector<int> ans(n);
    for (int b = 0; b < MAXB; b++)
        for (int i = 0; i < freq[b]; i++)
            ans[i] |= (1 << b);
    
    for (auto x: ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    precalc();
    int t; cin >> t;
    while (t--) solve();
}
