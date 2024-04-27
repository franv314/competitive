#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 1e9));
    vector<vector<int>> suff_min(N + 2, vector<int>(N + 2, 1e9));

    for (int i = N; i >= 0; i--) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = 1;
            suff_min[i][j] = min(suff_min[i + 1][j + 1], dp[i][j]);
        }

        for (int j = i + 1; j <= N; j++) {
            dp[i][j] = 1 + suff_min[i][j - i];
            suff_min[i][j] = min(suff_min[i + 1][j + 1], dp[i][j]);
        }
    }

    cout << dp[1][N] << '\n';
}