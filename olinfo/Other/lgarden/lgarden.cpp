#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    
    int N, M; cin >> N >> M;
    string S; cin >> S;

    vector<array<int, 3>> dp(N + 1);
    dp[0][0] = dp[0][1] = dp[0][2] = 1;

    for (int i = 1; i <= N; i++) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % M;
        dp[i][2] = dp[i - 1][1];
    }

    int cnt = 1;
    int curr = 0, ma = 0, mi = 0;

    for (int i = 0; i < N; i++) {
        if (S[i] == 'P') {
            int tcurr = curr - 1;
            int tmi = min(mi, tcurr);

            if (ma - tmi > 2) {
            } else if (ma - tmi == 2) {
                cnt = (cnt + dp[N - i - 1][tcurr - tmi]) % M;
            } else if (tmi == tcurr) {
                cnt = (cnt + dp[N - i - 1][0] + dp[N - i - 1][1] - 1 + M) % M;
            } else {
                cnt = (cnt + dp[N - i - 1][2] + dp[N - i - 1][1] - 1 + M) % M;
            }
        }

        if (S[i] == 'L') {
            mi = min(mi, --curr);
        } else {
            ma = max(ma, ++curr);
        }
    }

    cout << cnt << '\n';
}