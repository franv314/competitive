#include <bits/stdc++.h>
using namespace std;

typedef long double f80;
#define MAXK 100

f80 dp[8][8][8][8][MAXK + 1];

int main() {
    int k; scanf("%d", &k);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            dp[i][j][i][j][0] = 1.0;
    
    for (int i = 1; i <= k; i++) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                for (int tx = 0; tx < 8; tx++) {
                    for (int ty = 0; ty < 8; ty++) {
                        if (x == 0 && y == 0) {
                            dp[x][y][tx][ty][i] += dp[x + 1][y][tx][ty][i - 1] / 2.0;
                            dp[x][y][tx][ty][i] += dp[x][y + 1][tx][ty][i - 1] / 2.0;
                            continue;
                        }
                        if (x == 0 && y == 7) {
                            dp[x][y][tx][ty][i] += dp[x + 1][y][tx][ty][i - 1] / 2.0;
                            dp[x][y][tx][ty][i] += dp[x][y - 1][tx][ty][i - 1] / 2.0;
                            continue;
                        }
                        if (x == 7 && y == 0) {
                            dp[x][y][tx][ty][i] += dp[x - 1][y][tx][ty][i - 1] / 2.0;
                            dp[x][y][tx][ty][i] += dp[x][y + 1][tx][ty][i - 1] / 2.0;
                            continue;
                        }
                        if (x == 7 && y == 7) {
                            dp[x][y][tx][ty][i] += dp[x - 1][y][tx][ty][i - 1] / 2.0;
                            dp[x][y][tx][ty][i] += dp[x][y - 1][tx][ty][i - 1] / 2.0;
                            continue;
                        }
                        if (x == 0) {
                            dp[x][y][tx][ty][i] += dp[x + 1][y][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x][y + 1][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x][y - 1][tx][ty][i - 1] / 3.0;
                            continue;
                        }
                        if (x == 7) {
                            dp[x][y][tx][ty][i] += dp[x - 1][y][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x][y + 1][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x][y - 1][tx][ty][i - 1] / 3.0;
                            continue;
                        }
                        if (y == 0) {
                            dp[x][y][tx][ty][i] += dp[x][y + 1][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x + 1][y][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x - 1][y][tx][ty][i - 1] / 3.0;
                            continue;
                        }
                        if (y == 7) {
                            dp[x][y][tx][ty][i] += dp[x][y - 1][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x + 1][y][tx][ty][i - 1] / 3.0;
                            dp[x][y][tx][ty][i] += dp[x - 1][y][tx][ty][i - 1] / 3.0;
                            continue;
                        }
                        dp[x][y][tx][ty][i] += dp[x + 1][y][tx][ty][i - 1] / 4.0;
                        dp[x][y][tx][ty][i] += dp[x - 1][y][tx][ty][i - 1] / 4.0;
                        dp[x][y][tx][ty][i] += dp[x][y + 1][tx][ty][i - 1] / 4.0;
                        dp[x][y][tx][ty][i] += dp[x][y - 1][tx][ty][i - 1] / 4.0;
                    }
                }
            }
        }
    }

    f80 ans = 0.0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            f80 prob = 1.0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    prob *= (1.0 - dp[i][j][x][y][k]);
                }
            }
            ans += prob;
        }
    }

    printf("%.6Lf\n", ans);
}