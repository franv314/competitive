#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;
typedef long long i64;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<bool>> bad(n, vector<bool>(n));
    for (int i = 0; i < m; i++) {
        int j, x; cin >> j >> x;
        bad[j - 1][x - 1] = true;
    }

    vector<vector<pair<int, int>>> good(n);

    for (int x = 0; x < n; x++) {
        for (int s = 0; s < n - x; s++) {
            for (int r = 0; r <= s; r++) {
                bool ok = true;
                int pos = x;
                for (int i = r; i <= s; i++, pos++) {
                    ok &= !bad[pos][i];
                }
                for (int i = 0; i < r; i++, pos++) {
                    ok &= !bad[pos][i];
                }

                if (ok) {
                    good[x].emplace_back(s, r);
                }
            }
        }
    }

    vector<vector<i64>> dp(n + 1, vector<i64>(n + 1));
    dp[0][n] = 1;

    for (int len = 0; len < n; len++) {
        for (int last = 0; last <= n; last++) {
            for (auto [s, r]: good[len]) {
                if (r == last + 1 || len + s + 1 > n) continue;
                int new_last = r == 0 ? s : n;
                
                (dp[len + s + 1][new_last] += dp[len][last]) %= MOD;
            }
        }
    }

    cout << accumulate(dp[n].begin(), dp[n].end(), 0LL) % MOD << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
