#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector is_in_pref(n + 1, vector<bool>(n + 1, false));
    vector is_in_suff(n + 1, vector<bool>(n + 1, false));

    for (int i = 0; i < n; i++) {
        is_in_pref[i + 1] = is_in_pref[i];
        is_in_pref[i + 1][a[i]] = true;
    }
    for (int i = n - 1; i >= 0; i--) {
        is_in_suff[i] = is_in_suff[i + 1];
        is_in_suff[i][a[i]] = true;
    }

    vector dp(n + 1, vector<pair<int, int>>(n + 1));

    for (int len = 1; len <= n; len++) {
        for (int l = 0; l <= n - len; l++) {
            int r = l + len;

            bool l_in = is_in_pref[l][a[l]] || is_in_suff[r][a[l]];
            bool r_in = is_in_pref[l][a[r - 1]] || is_in_suff[r][a[r - 1]];

            pair<int, int> points_l = {!l_in + dp[l + 1][r].second, dp[l + 1][r].first};
            pair<int, int> points_r = {!r_in + dp[l][r - 1].second, dp[l][r - 1].first};
            
            dp[l][r] = max(points_l, points_r);
        }
    }

    cout << dp[0][n].first << ':' << dp[0][n].second << '\n';
}