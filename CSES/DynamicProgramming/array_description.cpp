#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<vector<unsigned>> dp(n, vector<unsigned>(m + 2));

    if (a[0] != 0) {
        dp[0][a[0]] = 1;
    } else {
        fill(dp[0].begin() + 1, dp[0].end() - 1, 1);
    }

    for (int i = 1; i < n; i++) {
        if (a[i] != 0) {
            dp[i][a[i]] = (dp[i - 1][a[i] - 1] + dp[i - 1][a[i]] + dp[i - 1][a[i] + 1]) % MOD;
        } else {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % MOD;
            }
        }
    }

    cout << accumulate(dp[n - 1].begin(), dp[n - 1].end(), 0LL) % MOD << '\n';
}