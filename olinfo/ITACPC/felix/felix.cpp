#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;

    vector<i64> l(n);
    for (auto &x: l) cin >> x;

    vector<i64> ps = l;
    for (int i = 1; i < n; i++)
        ps[i] += ps[i - 1];
    
    vector<i64> dp(n, 1e18);
    dp[0] = l[0];

    for (int i = 0; i < n - 1; i++) {
        dp[i + 1] = min(dp[i + 1], dp[i] + l[i + 1]);

        int b = lower_bound(ps.begin(), ps.end(), dp[i] + ps[i]) - ps.begin();
        if (b < n) {
            dp[b] = min(dp[b], ps[b] - ps[i]);
        } else {
            dp[n - 1] = min(dp[n - 1], dp[i]);
        }
    }

    cout << dp[n - 1] << '\n';
}