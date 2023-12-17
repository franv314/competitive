#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x; cin >> n >> x;

    vector<int> h(n), s(n);
    for (auto &x: h) cin >> x;
    for (auto &x: s) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(x + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= x; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= h[i - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j - h[i - 1]] + s[i - 1]);
        }
    }

    cout << *max_element(dp[n].begin(), dp[n].end()) << '\n';
}