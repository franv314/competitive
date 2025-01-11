#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

i64 MOD = 1e9 + 7;

i64 fexp(i64 b, i64 e) {
    i64 a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    }
    return a;
}

i64 eval_pow(i64 N, i64 K) {
    vector<i64> fact(K + 2), invs(K + 2), pows(K + 2);
    for (int i = 1; i < K + 2; i++)
        pows[i] = (pows[i - 1] + fexp(i, K)) % MOD;

    if (N < K + 2)
        return pows[N];

    fact[0] = 1;
    for (int i = 1; i < K + 2; i++)
        fact[i] = i * fact[i - 1] % MOD;

    invs.back() = fexp(fact.back(), MOD - 2);
    for (int i = K; i >= 0; i--)
        invs[i] = (i + 1) * invs[i + 1] % MOD;

    i64 eval_all = 1;
    for (int i = 0; i < K + 2; i++)
        eval_all = eval_all * (N - i) % MOD;
    
    i64 ans = 0;

    for (int i = 0; i < K + 2; i++) {
        i64 eval_here = fact[i] * fact[K + 1 - i] % MOD;
        if ((K + 1 - i) % 2)
            eval_here = (MOD - eval_here) % MOD;
        
        i64 coeff_here = fexp(eval_here, MOD - 2) * pows[i] % MOD;

        i64 prod_here = eval_all * fexp(N - i, MOD - 2) % MOD;
        ans = (ans + prod_here * coeff_here) % MOD;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    i64 N, K; cin >> N >> K >> MOD;

    N %= MOD;

    i64 p1 = (2 * N + 1) * eval_pow(N, K) % MOD;
    i64 p2 = 2LL * eval_pow(N, K + 1) % MOD;

    cout << (p1 - p2 + MOD) % MOD << '\n';
}