#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    int m = s.size();

    if (m > n) {
        cout << "0\n";
        return 0;
    }

    vector pref_match(m + 1, vector(26, 0));
    for (int i = 0; i <= m; i++) {
        for (char x = 'A'; x <= 'Z'; x++) {
            for (int j = 0; j <= i; j++) {
                string att = s.substr(j, i - j) + x;
                if (att == s.substr(0, i - j + 1)) {
                    pref_match[i][x - 'A'] = i - j + 1;
                    break;
                }
            }
        }
    }

    vector<bool> suff_match(m + 1);
    for (int i = 0; i <= m; i++) {
        string pref = s.substr(0, i);
        string suff = s.substr(m - i, i);

        suff_match[i] = pref == suff;
    }

    vector dp(n + 1, vector(m + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (char x = 0; x < 26; x++) {
                dp[i + 1][pref_match[j][x]] = (dp[i + 1][pref_match[j][x]] + dp[i][j]) % MOD;
            }
        }
    }

    vector<int> pows(n + 1);
    pows[0] = 1;
    for (int i = 1; i <= n; i++) {
        pows[i] = 26LL * pows[i - 1] % MOD;
    }

    int ans = 0;
    for (int i = 0; i <= n - m; i++) {
        int l = 0;
        for (int k = 0; k <= m; k++) {
            if (k == 0 || !suff_match[m - k]) {
                l = (l + dp[i][k]) % MOD;
            }
        }

        int r = pows[n - m - i];
        ans = (ans + (long long)l * r) % MOD;
    }

    cout << ans << '\n';
}