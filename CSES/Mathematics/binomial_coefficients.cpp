#include <bits/stdc++.h>
using namespace std;

#define MAXV 1'000'000
constexpr int MOD = 1e9 + 7;

int fexp(int base, int exp) {
    int ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (long long)ans * base % MOD;
        base = (long long)base * base % MOD;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    vector<int> fact(MAXV + 1), invs(MAXV + 1);
    fact[0] = 1;
    for (int i = 1; i <= MAXV; i++) fact[i] = (long long)i * fact[i - 1] % MOD;
    invs[MAXV] = fexp(fact[MAXV], MOD - 2);
    for (int i = MAXV - 1; i >= 0; i--) invs[i] = (long long)(i + 1) * invs[i + 1] % MOD;

    while (n--) {
        int a, b; cin >> a >> b;
        cout << (long long)fact[a] * invs[b] % MOD * invs[a - b] % MOD << '\n';
    }
}