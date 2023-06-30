#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

const int MOD = 1e9 + 7;
enum {A, B};

int dp[3001][3001][2];
int hor[3002][3001][2];
int diag[3002][3001][2];

int next_a[3000], next_b[3000];

int completa(int N, int M, int K, string S) {
    if (M == 1) {
        // Se K = N no, ma tentar non nuoce
        return 0;
    }

    int last_a = 0, last_b = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] == 'A') {
            for (; last_a < i; last_a++) next_a[last_a] = i;
        }
        if (S[i] == 'B') {
            for (; last_b < i; last_b++) next_b[last_b] = i;
        }
    }
    for (; last_a < N; last_a++) next_a[last_a] = 1e9;
    for (; last_b < N; last_b++) next_b[last_b] = 1e9;

    dp[N][K][A] = dp[N][K][B] = 1;
    hor[N][K][A] = hor[N][K][B] = 1;
    diag[N][K][A] = diag[N][K][B] = 1;

    int temp;
    for (int n = N - 1; n >= 0; n--) {
        for (int k = K; k >= 0; k--) {

            if (S[n] == 'B') {
                temp = 0;
            } else if (next_b[n] == 1e9) {
                temp = (hor[n + 1][k][B] - hor[n + M - 1][k][B] + diag[n + M - 1][k][B] + (long long)MOD) % MOD;
            } else if (next_b[n] >= n + M - 1) {
                temp = (
                    hor[n + 1][k][B]
                    - hor[n + M - 1][k][B]
                    + diag[n + M - 1][k][B]
                    - diag[next_b[n] + 1][k + next_b[n] - n - M + 2][B]
                    + 2 * (long long)MOD
                ) % MOD;
            } else {
                temp = (hor[n + 1][k][B] - hor[next_b[n] + 1][k][B] + MOD) % MOD;
            }

            dp[n][k][A] = temp;
            hor[n][k][A] = (hor[n + 1][k][A] + temp) % MOD;
            diag[n][k][A] = (diag[n + 1][k + 1][A] + temp) % MOD;

            if (S[n] == 'A') {
                temp = 0;
            } else if (next_a[n] == 1e9) {
                temp = (hor[n + 1][k][A] - hor[n + M - 1][k][A] + diag[n + M - 1][k][A] + (long long)MOD) % MOD;
            } else if (next_a[n] >= n + M - 1) {
                temp = (
                    hor[n + 1][k][A]
                    - hor[n + M - 1][k][A]
                    + diag[n + M - 1][k][A]
                    - diag[next_a[n] + 1][k + next_a[n] - n - M + 2][A]
                    + 2 * (long long)MOD
                ) % MOD;
            } else {
                temp = (hor[n + 1][k][A] - hor[next_a[n] + 1][k][A] + MOD) % MOD;
            }

            dp[n][k][B] = temp;
            hor[n][k][B] = (hor[n + 1][k][B] + temp) % MOD;
            diag[n][k][B] = (diag[n + 1][k + 1][B] + temp) % MOD;

            //cout << n _ k _ A _ "->" _ dp[n][k][A] << endl;
            //cout << n _ k _ B _ "->" _ dp[n][k][B] << endl;
        }
    }
    return (dp[0][0][A] + dp[0][0][B]) % MOD;
}