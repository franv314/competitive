#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

long long fexp(long long b, int e) {
    long long a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    }
    return a;
}

int main() {
    int n; cin >> n;
    
    if (n % 2) {
        cout << 0 << '\n';
        return 0;
    }
    n /= 2;

    long long ans = fexp(n + 1, MOD - 2);

    for (int i = 1; i <= n; i++) {
        ans = ans * (n + i) % MOD;
        ans = ans * fexp(i, MOD - 2) % MOD;
    }

    cout << ans << '\n';
}