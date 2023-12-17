#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    if ((N * (N + 1) / 2) & 1) return cout << "0\n", 0;

    vector<int> dp(N * (N + 1) / 2 + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = N * (N + 1) / 2 - i; j >= 0; j--) {
            (dp[j + i] += dp[j]) %= MOD;
        }
    }

    cout << dp[N * (N + 1) / 4] * (long long)((MOD + 1) / 2) % MOD << '\n';
}