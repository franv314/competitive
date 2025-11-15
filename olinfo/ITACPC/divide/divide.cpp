#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
constexpr i64 MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    i64 n; cin >> n;

    vector<i64> divisors;
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divisors.push_back(d);
            if (d * d != n) divisors.push_back(n / d);
        }
    }

    sort(divisors.begin(), divisors.end());
    map<i64, i64> dp;

    dp[1] = 1;
    for (auto d: divisors) {
        if (d == 1) continue;

        for (i64 x = 1; x * x <= d; x++) {
            if (d % x == 0) {
                (dp[d] += dp[x]) %= MOD;
                if (x * x != d && x != 1) (dp[d] += dp[d / x]) %= MOD;
            }
        }
    }

    cout << dp[n] << '\n';
}