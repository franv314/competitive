#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    vector<int> dp(N + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        dp[i] = accumulate(max(dp.begin() + i - 6, dp.begin()), dp.begin() + i, 0LL) % MOD;
    }
    cout << dp[N] << '\n';
}