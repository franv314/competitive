#include <bits/stdc++.h>
using namespace std;

#define MAXN 500
constexpr int MOD = 1e9 + 7;

int fact[MAXN + 1], invs[MAXN + 1];
int dp[MAXN + 1][MAXN + 1][2];

int fexp(int b, int e) {
    int ans = 1;
    for (; e; e >>= 1) {
        if (e & 1) ans = (long long)ans * b % MOD;
        b = (long long)b * b % MOD;
    }
    return ans;
}

void precalc() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) fact[i] = (long long)fact[i - 1] * i % MOD;
    invs[MAXN] = fexp(fact[MAXN], MOD - 2);
    for (int i = MAXN - 1; i >= 0; i--) invs[i] = (long long)invs[i + 1] * (i + 1) % MOD;
}

int binom(int n, int k) {
    return (long long)fact[n] * invs[k] % MOD * invs[n - k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    precalc();

    for (int i = 0; i <= s.size(); i++) dp[i][i][0] = dp[i][i][1] = 1;

    for (int len = 1; len <= s.size(); len++) {
        for (int l = 0; l <= s.size() - len; l++) {
            int r = l + len;
            
            dp[l][r][0] = dp[l][r][1] = (s[l] == s[r - 1]) * dp[l + 1][r - 1][1];
            for (int k = l + 2; k <= r - 2; k += 2) {
                int add = (long long)dp[l][k][0] * dp[k][r][1] % MOD * binom((r - l) / 2, (k - l) / 2) % MOD;
                dp[l][r][1] = (dp[l][r][1] + add) % MOD;
            }
        }
    }

    cout << dp[0][s.size()][1] << '\n';
}