#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, p; cin >> n >> k >> p;

    vector dp(n - 1, vector(k + 1, vector(k + 1, 0)));
    vector ps(n - 1, vector(k + 1, vector(k + 2, 0)));
    for (int x = 0; x <= k; x++) {
        for (int y = x; y <= k; y++) {
            dp[n - 2][y][x] = 1;
        }
    }

    for (int j = 0; j <= k; j++) {
        for (int l = 0; l <= k; l++) {
            ps[n - 2][j][l + 1] = (ps[n - 2][j][l] + dp[n - 2][j][l]) % p;
        }
    }

    for (int i = n - 3; i >= 0; i--) {
        for (int x = 0; x <= k; x++) {
            for (int y = 0; y <= k; y++) {
                dp[i][x][y] = (ps[i + 1][y][k + 1] - ps[i + 1][y][max(y - x, 0)] + p) % p;
            }
        }

        for (int j = 0; j <= k; j++) {
            for (int l = 0; l <= k; l++) {
                ps[i][j][l + 1] = (ps[i][j][l] + dp[i][j][l]) % p;
            }
        }
    }

    int ans = 0;
    for (int x = 0; x <= k; x++) {
        for (int y = x; y <= k; y++) {
            ans = (ans + dp[0][x][y]) % p;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}