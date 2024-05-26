#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    string S; cin >> S;

    vector<vector<int>> dp(N + 1, vector<int>(26, 1e9));
    dp.back().assign(26, 0);

    for (int i = N - 1; i >= 0; i--) {
        for (char c = 'a'; c <= 'z'; c++) {
            for (char att = c; att <= 'z'; att++) {
                dp[i][c - 'a'] = min(dp[i][c - 'a'], (att != S[i]) + dp[i + 1][att - 'a']);
            }
        }
    }

    int mi = *min_element(dp[0].begin(), dp[0].end());
    cout << mi << '\n';

    int used = 0;
    char last = 'a';

    for (int i = 0; i < N; i++) {
        for (char c = last; c <= 'z'; c++) {
            if (used + (c != S[i]) + dp[i + 1][c - 'a'] == mi) {
                if (c != S[i]) {
                    cout << i << " " << c << '\n';
                    used++;
                }

                last = c;
                break;
            }
        }
    }
}