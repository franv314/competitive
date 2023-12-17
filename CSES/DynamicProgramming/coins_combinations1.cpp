#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto &c: a) cin >> c;
    
    vector<int> dp(x + 1);
    dp[0] = 1;

    for (int i = 1; i <= x; i++) {
        for (auto c: a) {
            if (i - c < 0) continue;
            dp[i] = (dp[i] + dp[i - c]) % MOD;
        }
    }
    cout << dp[x] << '\n';
}