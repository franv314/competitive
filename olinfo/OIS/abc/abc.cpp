#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

constexpr int MOD = 1e9 + 7;
int fact[MAXN * 3 + 1];
int pows[MAXN * 3 + 1];

void precalc() {
    fact[0] = 1;
    pows[0] = 1;
    for (int i = 1; i <= 3 * MAXN; i++) {
        fact[i] = (long long)i * fact[i - 1] % MOD;
        pows[i] = 2 * pows[i - 1] % MOD;
    }
}

int fexp(int b, int e) {
    int a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = (long long)a * b % MOD;
        b = (long long)b * b % MOD;
    }
    return a;
}

int count_ways(int total, int odds, int evens) {
    if (odds + 2 * evens > total || odds < 0 || evens < 0) {
        return 0;
    }

    int ans = 0;

    if (odds > 0) {
        int type_a = odds - 1;
        int type_b = evens;
        int type_c = (total - 1 - type_a - 2 * type_b) / 2;

        ans += (long long)fact[type_a + type_b + type_c]
            * fexp(fact[type_a], MOD - 2) % MOD
            * fexp(fact[type_b], MOD - 2) % MOD
            * fexp(fact[type_c], MOD - 2) % MOD; 
    }

    if (evens > 0) {
        int type_a = odds;
        int type_b = evens - 1;
        int type_c = (total - 2 - type_a - 2 * type_b) / 2;

        ans += (long long)fact[type_a + type_b + type_c]
            * fexp(fact[type_a], MOD - 2) % MOD
            * fexp(fact[type_b], MOD - 2) % MOD
            * fexp(fact[type_c], MOD - 2) % MOD; 
    }

    return ans % MOD;
}

int solve(int A, int B, int C) {
    array<int, 3> vals = {A, B, C};
    sort(vals.rbegin(), vals.rend());

    tie(A, B, C) = tie(vals[0], vals[1], vals[2]);

    if (B == 0 && C == 0) {
        return A == 1;
    }

    long long ans = 0;

    for (int odds = B - C; odds <= B + C; odds += 2) {
        int bs = (B - C + odds) / 2;
        long long odd_ways = (long long)fact[odds]
            * fexp(fact[bs], MOD - 2) % MOD
            * fexp(fact[odds - bs], MOD - 2) % MOD;

        if (A + 1 - odds >= 0) {
            ans += odd_ways *
                count_ways(B + C, odds, A + 1 - odds) % MOD
                * pows[A + 1 - odds] % MOD;
        }

        if (A + 1 - odds >= 0) {
            ans += odd_ways *
                2LL * count_ways(B + C, odds, A - odds) % MOD
                * pows[A - odds] % MOD;
        }

        if (A + 1 - odds >= 0) {
            ans += odd_ways *
                count_ways(B + C, odds, A - 1 - odds) % MOD
                * pows[A - 1 - odds] % MOD;
        }

        ans %= MOD;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    precalc();
    
    int T; cin >> T;
    while (T--) {
        int A, B, C; cin >> A >> B >> C;
        cout << solve(A, B, C) << '\n';
    }
}