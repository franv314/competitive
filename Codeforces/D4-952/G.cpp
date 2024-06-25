#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int fexp(int b, int e) {
    int ans = 1;
    do {
        if (e & 1) ans = (long long)ans * b % MOD;
        b = (long long)b * b % MOD;
    } while (e >>= 1);
    return ans;
}

void solve() {
    int l, r, k; cin >> l >> r >> k;

    int ok_digits = 0;
    for (int i = 1; i <= 9; i++) {
        if ((long long)k * i <= 9) ok_digits++;
    }

    if (ok_digits == 0) {
        return void(cout << "0\n");
    }

    int hi = (long long)(fexp(ok_digits + 1, r) + MOD - 1) * fexp(ok_digits, MOD - 2) % MOD * ok_digits % MOD;
    int lo = l == 0 ? 0 : (long long)(fexp(ok_digits + 1, l) + MOD - 1) * fexp(ok_digits, MOD - 2) % MOD * ok_digits % MOD;

    cout << (hi - lo + MOD) % MOD << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}