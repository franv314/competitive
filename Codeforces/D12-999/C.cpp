#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;
typedef long long i64;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    if (n == 1)
        return void(cout << 1 + (a[0] == 0) << '\n');

    vector<i64> dp(n);
    dp[0] = a[0] == 0;
    dp[1] = (a[0] == 0 && a[1] == 0) + a[1] == 1;

    for (int i = 2; i < n; i++) {
        if (a[i] == a[i - 1])
            (dp[i] += dp[i - 1]) %= MOD;
        if (a[i] == a[i - 2] + 1)
            (dp[i] += dp[i - 2]) %= MOD;
    }

    cout << (dp[n - 1] + dp[n - 2]) % MOD << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
