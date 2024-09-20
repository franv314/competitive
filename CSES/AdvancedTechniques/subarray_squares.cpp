#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<long long> ps(n + 1);
    for (int i = 1; i <= n; i++)
        ps[i] = ps[i - 1] + a[i - 1];
    
    vector<long long> old_dp(n + 1), new_dp;
    for (int i = 0; i <= n; i++)
        old_dp[i] = ps[i] * ps[i];
    
    auto dnc = [&](auto &&dnc, int l, int r, int t, int b) {
        if (r - l < 1)
            return;

        int m = (l + r) / 2;
        pair<long long, int> best = {1e18, -1};

        for (int i = t; i < min(b, m); i++) {
            best = min(best, {old_dp[i] + (ps[m] - ps[i]) * (ps[m] - ps[i]), i});
        }

        new_dp[m] = best.first;
        
        dnc(dnc, l, m, t, best.second + 1);
        dnc(dnc, m + 1, r, best.second, b);
    };

    for (int i = 1; i < k; i++) {
        new_dp.assign(n + 1, 1e18);
        dnc(dnc, 1, n + 1, 1, n + 1);
        old_dp = new_dp;
    }

    cout << old_dp[n] << '\n';
}
