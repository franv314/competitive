#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, M; cin >> N >> M;
    vector<string> arr(N);

    for (auto &row: arr)
        cin >> row;

    int ans = 0;
    if (M >= 3) {
        vector<array<int, 8>> dp(M + 1);
        dp[2] = {0, (int)1e9, 1, (int)1e9, 1, (int)1e9, 2, (int)1e9};

        for (int i = 2; i < M; i++) {
            fill(dp[i + 1].begin(), dp[i + 1].end(), (int)1e9);
            
            for (int j = 0; j < 8; j++) {
                dp[i + 1][j >> 1] = min(dp[i + 1][j >> 1], dp[i][j]);
                dp[i + 1][(j >> 1) | 4] = min(dp[i + 1][(j >> 1) | 4], dp[i][j] + 1);
            }

            bool ok = true;
            for (int j = 0; j < N; j++) {
                int mask = (arr[j][i - 2] == '1')
                         | ((arr[j][i - 1] == '1') << 1)
                         | ((arr[j][i - 0] == '1') << 2);
                dp[i + 1][mask] = dp[i + 1][7 ^ mask] = 1e9;
            }

            if (!ok)
                dp[i + 1][0] = dp[i + 1][7] = 1e9;
        }

        ans += *min_element(dp[M].begin(), dp[M].end());
    }
    
    if (N >= 3) {
        vector<array<int, 8>> dp(N + 1);
        dp[2] = {0, (int)1e9, 1, (int)1e9, 1, (int)1e9, 2, (int)1e9};

        for (int i = 2; i < N; i++) {
            fill(dp[i + 1].begin(), dp[i + 1].end(), (int)1e9);
            
            for (int j = 0; j < 8; j++) {
                dp[i + 1][j >> 1] = min(dp[i + 1][j >> 1], dp[i][j]);
                dp[i + 1][(j >> 1) | 4] = min(dp[i + 1][(j >> 1) | 4], dp[i][j] + 1);
            }

            bool ok = true;
            for (int j = 0; j < M; j++) {
                int mask = (arr[i - 2][j] == '1')
                         | ((arr[i - 1][j] == '1') << 1)
                         | ((arr[i - 0][j] == '1') << 2);
                dp[i + 1][mask] = dp[i + 1][7 ^ mask] = 1e9;
            }

            
            if (!ok)
                dp[i + 1][0] = dp[i + 1][7] = 1e9;
        }

        ans += *min_element(dp[N].begin(), dp[N].end());
    }

    if (ans >= 1e9)
        ans = -1;

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}