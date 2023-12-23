#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;

    auto neg = [&](int x) { return ((1 << n) - 1) ^ x; };

    vector<vector<int>> masks(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << n); j++) {
            if ((j | neg(i)) != neg(i)) continue;

            bool ok = true;
            int len = 0;
            for (int k = 0; k < n; k++) {
                if (((j >> k) & 1) || ((i >> k) & 1)) {
                    ok &= (len & 1) == 0;
                    len = 0;
                } else len++;
            }
            ok &= (len & 1) == 0;

            if (ok) masks[i].push_back(j);
        }
    }

    vector<vector<int>> dp(m + 1, vector<int>(1 << n));
    dp[0][0] = 1;

    for (int i = 1; i <= m; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            for (auto m2: masks[mask]) {
                (dp[i][mask] += dp[i - 1][m2]) %= MOD;
            }
        }
    }

    cout << dp[m][0] << '\n';
}