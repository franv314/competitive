#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector dp(n, vector(11, -1));
    dp[0][6] = 6;

    for (int i = 1; i < n; i++) {
        for (auto rem: {6, 3}) {
            for (int rem2 = 0; rem2 < 11; rem2++) {
                if (dp[i - 1][rem2] == -1) continue;
                if (i % 2) {
                    dp[i][(11 + rem2 - rem) % 11] = rem;
                } else {
                    dp[i][(rem2 + rem) % 11] = rem;
                }
            }
        }
    }

    if (dp[n - 1][0] == -1) return void(cout << "-1\n");
    
    for (int d = n - 1, curr = 0; d >= 0; d--) {
        cout << dp[d][curr];
        if (d % 2)
            (curr += dp[d][curr]) %= 11;
        else
            (curr += 11 - dp[d][curr]) %= 11;
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}