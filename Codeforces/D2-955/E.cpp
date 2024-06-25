#include <bits/stdc++.h>
using namespace std;

#define MAXLOG 61
constexpr int MOD = 1e9 + 7;

int dp[MAXLOG][MAXLOG];

void precalc() {
    for (int i = 1; i < MAXLOG; i++) {
        dp[i][0] = 1;
        for (int j = 1; j < MAXLOG; j++) {
            if (j >= i) {
                dp[i][j] = ((1LL << i) % MOD) * (((1LL << i) + 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD;
            } else if (j == i - 1) {
                dp[i][j] = ((1LL << i) % MOD) * (((1LL << i) - 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD;
            } else {
                dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
    }
}

void solve() {
    long long n; cin >> n;
    int k; cin >> k;

    int ans = 0;
    for (int bit = 60; bit >= 0; bit--) {
        if (k < 0) break;
        if ((1LL << bit) > n) continue;

        if (k >= bit) {
            n--;
            if (__builtin_popcountll(n) > k) n--;
            ans = (ans + ((n + 1) % MOD) * ((n + 2) % MOD) % MOD * ((MOD + 1) / 2) % MOD) % MOD;
            break;
        }

        ans = (ans + dp[bit][k]) % MOD;
        n -= (1LL << bit);
        k--;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    precalc();
    int t; cin >> t;
    while (t--) solve();
}