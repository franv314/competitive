#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<array<int, 4>> dp(n + 1);
    dp[0][1] = dp[0][2] = dp[0][3] = 1e8;

    for (int i = 0; i < n; i++) {
        dp[i + 1][1] = dp[i + 1][2] = dp[i + 1][3] = 1e8;
        dp[i + 1][0] = 1 + *min_element(dp[i].begin(), dp[i].end());
        
        if (a[i] <= 4) {
            int new_cover = 0;
            if (a[i] > 0) new_cover |= 1;
            if (a[i] > 2) new_cover |= 2;

            for (int old_cover = 0; old_cover < 4; old_cover++) {
                dp[i + 1][new_cover & ~old_cover] =  min(
                    dp[i + 1][new_cover & ~old_cover],
                    __builtin_popcount(new_cover & ~old_cover) + dp[i][old_cover]
                );
            }
        }
    }

    cout << *min_element(dp[n].begin(), dp[n].end()) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}