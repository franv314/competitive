#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, R, T, L; scanf("%d%d%d%d", &N, &R, &T, &L);
    vector<int> X(N);
    for (auto &x: X) scanf("%d", &x);

    X.push_back(L);
    vector<vector<int>> dp(N + 1, vector<int>(R + 1, INT_MAX));
    fill(dp[0].begin(), dp[0].end(), X[0]);

    for (int i = 0; i < N; i++) {
        int dist = X[i + 1] - X[i];

        for (int j = 0; j <= R; j++) {
            int rem = dp[i][j] % (2 * T);
            if (rem < T) {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + dist);
            } else {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 2 * T - rem + dist);
                if (j > 0) {
                    dp[i + 1][j - 1] = min(dp[i + 1][j - 1],  dp[i][j] + dist);
                }
            }
        }
    }

    printf("%d\n", dp[N][0]);
}