#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    vector<int> dp(N + 1, 0);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        dp[i] = 1e9;
        for (int j = i; j; j /= 10) {
            dp[i] = min(dp[i], 1 + dp[i - j % 10]);
        }
    }

    cout << dp[N] << '\n';
}