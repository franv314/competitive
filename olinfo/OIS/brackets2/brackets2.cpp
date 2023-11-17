#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (auto &x: A) cin >> x;

    int s = accumulate(A.begin(), A.end(), 0);

    vector<vector<int>> dp(N + 1, vector<int>(s + 1));
    dp[N][0] = true;

    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j <= s; j++) {
            if (j + A[i] <= s) dp[i][j] |= dp[i + 1][j + A[i]];
            if (j - A[i] >= 0) dp[i][j] |= dp[i + 1][j - A[i]];
        }
    }

    if (!dp[0][0]) return cout << -1 << '\n', 0;

    int k = 0;
    for (int i = 0; i < N; i++) {
        if (k - A[i] >= 0 && dp[i + 1][k - A[i]]) {
            cout << string(A[i], ')');
            k -= A[i];
        } else {
            cout << string(A[i], '(');
            k += A[i];
        }
    }

    cout << '\n';
}