#include <bits/stdc++.h>
using namespace std;

typedef uint64_t hash_t;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    string s; cin >> s;
    vector<vector<int>> dp(s.size(), vector<int>(s.size()));

    for (int l = 0; l < s.size(); l++) dp[l][l] = 1;
    hash_t inv = 1;
    for (int d = 1; d < s.size(); d++) {
        inv *= 29;
        hash_t dir = 0, rev = 0;
        for (int i = 0; i <= d; i++) {
            dir = dir * 29 + s[i] - 'a';
            rev = rev * 29 + s[d - i] - 'a';
        }
        for (int l = 0; l < s.size() - d; l++) {
            int r = l + d;
            dp[l][r] = dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1] + (dir == rev);

            dir -= inv * (s[l] - 'a');
            rev = (rev - s[l] + 'a') * 3816567739388183093ULL;

            if (r != s.size() - 1) {
                dir = dir * 29 + s[r + 1] - 'a';
                rev += inv * (s[r + 1] - 'a');
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << dp[l - 1][r - 1] << '\n';
    }
}