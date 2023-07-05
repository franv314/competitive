#include <bits/stdc++.h>
using namespace std;

const int MOD = 2011;

ifstream in("input.txt");
ofstream out("output.txt");

char inv(char c) {
    return c == '0' ? '1' : '0';
}

int main() {
    int M, N; in >> M >> N;
    string S; in >> S;
    
    vector<int> longest_match(M);
    for (int i = 0; i < M; i++) {
        string curr = S.substr(0, i) + inv(S[i]);
        for (int j = 0; j <= curr.size(); j++) {
            if (curr.substr(i - j + 1) == S.substr(0, j)) {
                longest_match[i] = j;
            }
        }
    }
    
    vector dp(N + 1, vector(M, 0));
    dp[0][0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j + 1 != M) (dp[i + 1][j + 1] += dp[i][j]) %= MOD;
            (dp[i + 1][longest_match[j]] += dp[i][j]) %= MOD;
        }
    }
    
    out << accumulate(dp[N].begin(), dp[N].end(), 0) % MOD;
}