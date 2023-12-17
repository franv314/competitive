#include <bits/stdc++.h>
using namespace std;

#define MAXN 1'000'000
constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    vector<array<int, 3>> dp(MAXN + 1);
    dp[0] = {1, 0, 0};

    for (int i = 1; i <= MAXN; i++) {
        dp[i][0] = (2LL * dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % MOD;
        dp[i][1] = (3LL * dp[i - 1][0] + 3LL * dp[i - 1][1]) % MOD;
        dp[i][2] = (dp[i - 1][0] + dp[i - 1][2]) % MOD;
    }

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        cout << dp[n][0] << '\n';
    }
}