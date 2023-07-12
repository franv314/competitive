#include <bits/stdc++.h>
using namespace std;

#define MAXL 10'001
#define INF (long long)(2e18)

long long dp[MAXL][27][27];
vector<int> adj[27][27];

int main() {
    long long N, L, K; cin >> N >> L >> K;
    for (int i = 0; i < K; i++) {
        string S; cin >> S;
        adj[S[0] - 'a'][S[1] - 'a'].push_back(S[2] - 'a');
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            dp[L][i][j] = 1;
        }
    }
    
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 26; j++) {
            adj[26][i].push_back(j);
        }
    }
    
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            sort(adj[i][j].begin(), adj[i][j].end());
        }
    }
    
    for (int l = L - 1; l >= 0; l--) {
        for (int x = 0; x < 27; x++) {
            for (int y = 0; y < 27; y++) {
                for (auto z: adj[x][y]) {
                    dp[l][x][y] += dp[l + 1][y][z];
                    dp[l][x][y] = min(dp[l][x][y], INF);
                }
            }
        }
    }
    
    int x = 26, y = 26;
    long long count = 0;
    for (int l = 0; l < L; l++) {
        for (auto z: adj[x][y]) {
            if (count + dp[l + 1][y][z] < N) {
                count += dp[l + 1][y][z];
            } else {
                cout << (char)(z + 'a');
                x = y;
                y = z;
                break;
            }
        }
    }
}