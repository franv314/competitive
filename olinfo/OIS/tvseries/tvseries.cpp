#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, D; cin >> N >> D;

    vector<int> S(N), E(N), X(N);
    for (auto &x: S) {
        cin >> x;
        x--;
    }
    for (auto &x: E) {
        cin >> x;
        x--;
    }
    for (auto &x: X) cin >> x;

    vector<vector<int>> dp(N + 1, vector<int>(3 * D));

    for (int i = N - 1; i >= 0; i--) {
        for (int j = D - 1; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j];

            int first_day = j + X[i];
            int watching = max(0, E[i] - max(S[i], first_day) + 1);

            dp[i][j] = max(dp[i][j], watching + dp[i + 1][j + X[i]]);
        }
    }

    cout << dp[0][0] << '\n';
}