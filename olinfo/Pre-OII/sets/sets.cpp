#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define MAXN 10000

bool ok[MAXN][MAXN + 1];
int pxor[MAXN + 1];
int dp[MAXN + 1];

int conta(int N, vector<int> V) {
    for (int i = 0; i < N; i++) {
        pxor[i + 1] = pxor[i] ^ V[i];
    }

    for (int i = 0; i < N; i++) {
        ok[i][i] = true;
    }

    for (int len = 3; len <= N; len += 3) {
        for (int l = 0; l <= N - len; l++) {
            int r = l + len;
            ok[l][r] |= ok[l    ][r - 3] && (V[r - 3] ^ V[r - 2] ^ V[r - 1]) == 0;
            ok[l][r] |= ok[l + 1][r - 2] && (V[l    ] ^ V[r - 2] ^ V[r - 1]) == 0;
            ok[l][r] |= ok[l + 2][r - 1] && (V[l    ] ^ V[l + 1] ^ V[r - 1]) == 0;
            ok[l][r] |= ok[l + 3][r    ] && (V[l    ] ^ V[l + 1] ^ V[l + 2]) == 0;
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        dp[i] = dp[i + 1];
        for (int len = 3; i + len <= N; len += 3) {
            if ((pxor[i] ^ pxor[i + len]) == 0) {
                dp[i] = max(dp[i], len + dp[i + len]);
            }
        }
    }
    return dp[0];
}