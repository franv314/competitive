#include <bits/stdc++.h>
using namespace std;

#define MAXL 10'001
typedef long double f80;

long long N, L, K;
f80 dp[MAXL][27][27];
vector<int> adj[27][27];
vector<string> words;

f80 rec(int len, string s) {
    if (len == L) {
        words.push_back(s);
        return 1;
    }
    long long cnt = 0;
    if (len < 2) {
        for (int x = 0; x < 26; x++)
            cnt += rec(len + 1, s + (char)('a' + x));
    } else {
        for (auto x: adj[s[len - 2] - 'a'][s[len - 1] - 'a'])
            cnt += rec(len + 1, s + (char)('a' + x));
        assert(dp[len][s[len - 2] - 'a'][s[len - 1] - 'a'] == cnt);
    }
    return cnt;
}

int main() {
    cin >> N >> L >> K;
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
    
    for (int l = L - 1; l >= 0; l--) {
        for (int x = 0; x < 27; x++) {
            for (int y = 0; y < 27; y++) {
                for (auto z: adj[x][y]) {
                    dp[l][x][y] += dp[l + 1][y][z];
                }
            }
        }
    }
    
    rec(0, "");
    
    int x = 26, y = 26;
    f80 count = 0;
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