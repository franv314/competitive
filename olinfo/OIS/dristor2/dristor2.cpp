#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define _ << " " <<
#define MAXN 14
#define MAXM 100

const int MOD = 1e9 + 7;

int dp[1 << MAXN][MAXM][MAXN + 1];

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> L(M);
    bool sub_1 = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int temp;
            cin >> temp;
            sub_1 *= temp;
            L[j] = (L[j] << 1) | temp;
        }
    }

    if (sub_1) {
        long long res = 1;
        for (int i = M; i > M - N; i--)
            res = (res * i) % MOD;
        cout << res << endl;
        return 0;
    }

    for (int taken = 0; taken < (1 << N); taken++) {
        int takeable = L[M - 1] & ~taken;
        dp[taken][M - 1][0] = 1;
        for (int mask = 1; mask < (1 << N); mask <<= 1) {
            if (mask & takeable)
                dp[taken][M - 1][1]++;   
        }
    }

    for (int m = M - 2; m >= 0; m--) {
        for (int taken = 0; taken < (1 << N); taken++) {
            int takeable = L[m] & ~taken;
            for (int n = 0; n <= M - m; n++) {
                dp[taken][m][n] = dp[taken][m + 1][n];
            }
            for (int mask = 1; mask < (1 << N); mask <<= 1) {
                if (mask & takeable)
                    for (int n = 1; n <= N; n++)
                        dp[taken][m][n] = (dp[taken][m][n] + dp[taken | mask][m + 1][n - 1]) % MOD;
            }
        }
    }

    int i = N;
    while (!dp[0][0][i]) i--;

    cout << dp[0][0][i] << endl;

    return 0;
}