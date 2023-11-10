#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int fexp(int base, int exp) {
    int ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (long long)base * ans % MOD;
        base = (long long)base * base % MOD;
    }
    return ans;
}

int main() {
    int n, m; cin >> n >> m;
    vector<int> pows(n + 1, 1);
    for (int i = 1; i <= n; i++) pows[i] = m * (long long)pows[i - 1] % MOD;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + pows[gcd(i, n)]) % MOD;
    }

    cout << (long long)ans * fexp(n, MOD - 2) % MOD << '\n';
}