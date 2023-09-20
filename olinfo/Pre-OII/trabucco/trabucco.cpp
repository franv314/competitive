#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int ContaPercorsi(int N, int M, int K, int* X, int* Y) {
    vector<vector<int>> dst(N, vector<int>(M, -1));
    queue<tuple<int, int, int>> q;
    
    for (int i = 0; i < K; i++) {
        q.emplace(X[i], Y[i], 0);
    }
    
    while (!q.empty()) {
        auto [x, y, d] = q.front(); q.pop();
        if (dst[x][y] != -1) continue;
        dst[x][y] = d;
        
        if (x > 0)     q.emplace(x - 1, y, d + 1);
        if (x < N - 1) q.emplace(x + 1, y, d + 1);
        if (y > 0)     q.emplace(x, y - 1, d + 1);
        if (y < M - 1) q.emplace(x, y + 1, d + 1);
    }
            
    vector<vector<int>> max_safety = dst;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 && j == 0) continue;
            int max_to = INT_MIN;
            if (i > 0) max_to = max(max_to, max_safety[i - 1][j]);
            if (j > 0) max_to = max(max_to, max_safety[i][j - 1]);
            max_safety[i][j] = min(max_safety[i][j], max_to);;
        }
    }
    
    int ma = max_safety[N - 1][M - 1];
    
    vector<vector<int>> dp(N, vector<int>(M));
    dp[0][0] = 1;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (dst[i][j] < ma) continue;
            if (i > 0) (dp[i][j] += dp[i - 1][j]) %= MOD;
            if (j > 0) (dp[i][j] += dp[i][j - 1]) %= MOD;
        }
    }
    
    return dp[N - 1][M - 1];
}