#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define MAXN 500
#define MAXK 21

const int MOD = 998'244'353;

int dp[MAXN][MAXN][MAXK];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;

    int grid[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];
    
    int x = grid[0][0];
    int div = 1;
    for (int i = 2; i <= x; i++) {
        while (x % i == 0) {
            x /= i;
            if (k % (div * i) == 0) div *= i;
        }
    }
    dp[0][0][div] = 1;
    for (int d = 1; d < n + n - 1; d++) {
        for (int y = 0; y <= d; y++) {
            int x = d - y;
            if (x >= n || y >= n || grid[x][y] == -1) continue;
            
            for (int div = 1; div <= k; div++) {
                if (k % div) continue;

                int ndiv = div;
                int X = grid[x][y];
                for (int i = 2; i <= k; i++) {
                    while (X % i == 0) {
                        X /= i;
                        if (k % (ndiv * i) == 0) ndiv *= i;
                    }
                }
                if (x > 0) {
                    dp[x][y][ndiv] = (dp[x][y][ndiv] + dp[x - 1][y][div]) % MOD;
                }
                if (y > 0) {
                    dp[x][y][ndiv] = (dp[x][y][ndiv] + dp[x][y - 1][div]) % MOD;
                }
                //cout << x _ y _ ndiv << endl;//_ dp[x][y][ndiv] << endl;
            }
        }
    }

    cout << dp[n - 1][n - 1][k] << endl;
}