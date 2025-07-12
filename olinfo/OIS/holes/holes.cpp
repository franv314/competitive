#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

i64 fexp(i64 b, i64 e, i64 mod){
    i64 a = 1;
    do {
        if (e & 1) a = a * b % mod;
        b = b * b % mod;
    } while (e >>= 1);
    return a;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, mod; cin >> n >> mod;

    vector<i64> pows(n + 1), fact(n + 1), inv_pows(n + 1), inv_fact(n + 1);

    pows[0] = fact[0] = inv_pows[0] = 1;
    for (int i = 1; i <= n; i++) {
        pows[i] = 2 * pows[i - 1] % mod;
        inv_pows[i] = ((mod + 1) / 2) * inv_pows[i - 1] % mod;
        fact[i] = i * fact[i - 1] % mod;
    }

    inv_fact[n] = fexp(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (i + 1) * inv_fact[i + 1] % mod;
    }

    auto binom = [&](int n, int k) {
        return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
    };

    vector<i64> ps(n + 1), good(n + 1);
    good[0] = 1;
    ps[0] = good[0] * inv_fact[1] % mod * inv_pows[1] % mod;

    for (int i = 1; i <= n; i++) {
        good[i] = pows[i] * fact[i] % mod * (mod + 1 - ps[i - 1]) % mod;
        if (i != n) ps[i] = (ps[i - 1] + good[i] * inv_fact[i + 1] % mod * inv_pows[i + 1] % mod) % mod;
    }

    for (int i = 0; i <= n; i++) {
        cout << good[i] * good[n - i] % mod * binom(n, i) % mod << ' ';
    }
    cout << '\n';
}
