#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long fexp(long long base, long long exp) {
    long long curr = base, ans = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) (ans *= curr) %= MOD;
        (curr *= curr) %= MOD;
    }
    return ans;
}

int main() {
    int n, m; cin >> n >> m;
    long long ans = 1;
    for (int i = 1; i <= n + m - 1; i++) {
        (ans *= i) %= MOD;
    }
    for (int i = 1; i <= m; i++) {
        (ans *= fexp(i, MOD - 2)) %= MOD;
    }
    for (int i = 1; i <= n - 1; i++) {
        (ans *= fexp(i, MOD - 2)) %= MOD;
    }
    cout << ans;
}