#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<long long> ps(n + 1);
    for (int i = 0; i < n; i++) ps[i + 1] = ps[i] + a[i];

    vector<long long> dp(n + 1);
    pair<long long, int> ma = {0, n};

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = dp[ma.second] + ps[n] - ps[i];
        ma = max(ma, {dp[i], i});
    }

    cout << dp[0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}