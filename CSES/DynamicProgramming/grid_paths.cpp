#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    if (grid[n - 1][n - 1] == '*') return cout << "0\n", 0;

    vector<vector<int>> dp(n, vector<int>(n));
    dp[n - 1][n - 1] = 1;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (grid[i][j] == '*') continue;
            if (i < n - 1) (dp[i][j] += dp[i + 1][j]) %= MOD;
            if (j < n - 1) (dp[i][j] += dp[i][j + 1]) %= MOD;
        }
    }

    cout << dp[0][0] << '\n';
}