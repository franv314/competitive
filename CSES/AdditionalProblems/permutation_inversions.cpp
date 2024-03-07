#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;

    vector dp(n + 1, vector(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        int running_sum = 0;
        for (int j = 0; j <= k; j++) {
            running_sum = (running_sum + dp[i - 1][j]) % MOD;
            if (j - i >= 0) running_sum = (running_sum - dp[i - 1][j - i] + MOD) % MOD;

            dp[i][j] = running_sum;
        }
    }

    cout << dp[n][k] << '\n';
}