#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    string S; cin >> S;

    vector<int> qps(N + 1);
    for (int i = 1; i <= N; i++)
        qps[i] = qps[i - 1] + (S[i - 1] == '?');
    
    int cnta = count(S.begin(), S.end(), 'A');
    int cntb = count(S.begin(), S.end(), 'B');
    
    vector dp(3, vector(N, vector(N + 1, vector(N + 1, (short)1e4))));
    dp[0][0][1][0] = 0;

    for (int pos = 1; pos < N; pos++) {
        for (int l = 0; l < 3; l++) {
            if (S[pos] != '?' && S[pos] != 'A' + l) continue;

            for (int a = 0; a <= N; a++) {
                for (int b = 0; b <= N; b++) {
                    if (a == 0 && l == 0) continue;
                    if (b == 0 && l == 1) continue;

                    switch (l) {
                    case 0: dp[0][pos][a][b] = min<int>({
                            dp[0][pos - 1][a - 1][b],
                            dp[1][pos - 1][a - 1][b] + 1,
                            dp[2][pos - 1][a - 1][b] + 1
                        });
                        break;
                    case 1: dp[1][pos][a][b] = min<int>({
                            dp[0][pos - 1][a][b - 1] + 1,
                            dp[1][pos - 1][a][b - 1],
                            dp[2][pos - 1][a][b - 1] + 1
                        });
                        break;
                    case 2: dp[2][pos][a][b] = min<int>({
                            dp[0][pos - 1][a][b] + 1,
                            dp[1][pos - 1][a][b] + 1,
                            dp[2][pos - 1][a][b]
                        });
                        break;
                    }
                }
            }
        }
    }

    int Q; cin >> Q; 
    while (Q--) {
        int X, Y, Z; cin >> X >> Y >> Z;
        cout << dp[0][N - 1][X + cnta][Y + cntb] << '\n';
    }
}