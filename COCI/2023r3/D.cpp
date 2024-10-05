#include <bits/stdc++.h>
using namespace std;

#define MAXN 500
#define MAXD 240

int MOD = 998244353;

int grid[MAXN][MAXN];
int dp[MAXN][MAXN][MAXD];
int transition[MAXD][MAXD];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    
    int cnt = 0;
    vector<int> div_val(k + 1);
    vector<int> div;
    for (int i = 1; i <= k; i++) {
        if (k % i == 0) {
            div_val[i] = cnt++;
            div.push_back(i);
        }
    }
    
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
            int new_state = div_val[gcd((int64_t)div[i] * div[j], k)];
            transition[i][j] = new_state;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] != -1) grid[i][j] = div_val[gcd(grid[i][j], k)];
        }
    }   
    
    dp[0][0][grid[0][0]] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == -1) continue;
            
            for (int d = 0; d < cnt; d++) {
                int new_state = transition[grid[i][j]][d];
                
                if (i > 0) (dp[i][j][new_state] += dp[i - 1][j][d]) %= MOD;
                if (j > 0) (dp[i][j][new_state] += dp[i][j - 1][d]) %= MOD;
            }
        }
    }
    
    cout << dp[n - 1][n - 1][cnt - 1] << '\n';
}