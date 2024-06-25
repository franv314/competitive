#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, l, r; cin >> n >> l >> r;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<long long> ps(n + 1);
    for (int i = 0; i < n; i++) {
        ps[i + 1] = ps[i] + a[i];
    }

    vector<int> dp(n + 1);

    for (int i = n - 1; i >= 0; i--) {
        int idx = lower_bound(ps.begin(), ps.end(), ps[i] + l) - ps.begin();
        if (idx == n + 1) {
            dp[i] = dp[i + 1];
            continue;
        }
        dp[i] = max(dp[i + 1], dp[idx] + ((ps[idx] - ps[i]) <= r));
    }

    cout << dp[0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}