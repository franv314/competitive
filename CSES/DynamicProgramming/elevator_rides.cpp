#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x; cin >> n >> x;
    vector<int> w(n);
    for (auto &a: w) cin >> a;

    vector<array<int, 2>> dp(1 << n, {INT_MAX, INT_MAX});
    dp[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                auto [rides, weight] = dp[mask ^ (1 << i)];
                if (weight + w[i] <= x) {
                    weight += w[i];
                } else {
                    weight = w[i];
                    rides++;
                }
                dp[mask] = min(dp[mask], {rides, weight});
            }
        }
    }

    cout << dp.back()[0] << '\n';
}