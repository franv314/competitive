#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;

long long fexp(long long b, int e) {
    long long a = 1;
    for (; e; e >>= 1) {
        if (e & 1) a = a * b % MOD;
        b = b * b % MOD;
    }
    return a;
}

void solve() {
    int N, X; cin >> N >> X;
    vector<int> T(N);
    for (auto &t: T) cin >> t;

    int single_chance = fexp(N, MOD - 2);

    vector<int> dp(X + 1);
    for (int x = X; x >= 0; x--) {
        for (int i = 0; i  < N; i++) {
            if (x + T[i] > X) {
                if (i == 0) {
                    dp[x] = (dp[x] + single_chance) % MOD;
                }
            } else {
                dp[x] = (dp[x] + (long long)dp[x + T[i]] * single_chance) % MOD;
            }
        }
    }
    cout << dp[0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}