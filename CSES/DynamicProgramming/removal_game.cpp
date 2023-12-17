#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector dp(n + 1, vector<pair<long long, long long>>(n + 1));

    for (int len = 1; len <= n; len++) {
        for (int l = 0; l <= n - len; l++) {
            int r = l + len;
            
            pair<long long, long long> lm = {dp[l + 1][r].second + a[l], dp[l + 1][r].first};
            pair<long long, long long> rm = {dp[l][r - 1].second + a[r - 1], dp[l][r - 1].first};

            dp[l][r] = max(lm, rm);
        }
    }

    cout << dp[0][n].first << '\n';
}