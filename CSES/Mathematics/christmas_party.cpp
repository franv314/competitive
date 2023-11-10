#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    int N; cin >> N;
    vector<int> dp(N + 1);
    dp[0] = 1, dp[1] = 0;
    for (int i = 2; i <= N; i++) {
        dp[i] = (i - 1LL) * (dp[i - 2] + dp[i - 1]) % MOD;
    }
    cout << dp[N] << '\n';
}