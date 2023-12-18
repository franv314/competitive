#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    string s; cin >> s;
    string t; cin >> t;

    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));
    for (int i = 0; i <= s.size(); i++) dp[i][t.size()] = s.size() - i;
    for (int i = 0; i <= t.size(); i++) dp[s.size()][i] = t.size() - i;

    for (int i = s.size() - 1; i >= 0; i--) {
        for (int j = t.size() - 1; j >= 0; j--) {
            if (s[i] == t[j]) {
                dp[i][j] = min({dp[i + 1][j + 1], dp[i][j + 1] + 1, dp[i + 1][j] + 1});
            } else {
                dp[i][j] = min({dp[i + 1][j + 1] + 1, dp[i][j + 1] + 1, dp[i + 1][j] + 1});
            }
        }
    }

    cout << dp[0][0] << '\n';
}