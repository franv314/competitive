#include <bits/stdc++.h>
using namespace std;

#define MAXA 100
#define MAXN 100'000

const int MOD = 1e9 + 7;

int dp[MAXA + 1][MAXN + 1];

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    string A; in >> A;
    string S; in >> S;

    int len_a = A.size();
    int len_s = S.size();

    A.push_back('$');

    dp[len_a][len_s] = 1;
    for (int s = len_s - 1; s >= 0; s--) {
        for (int a = len_a; a >= 0; a--) {
            if (A[a] == S[s]) {
                dp[a][s] = (dp[a + 1][s + 1] + dp[a][s + 1]) % MOD;
            } else {
                dp[a][s] = dp[a][s + 1];
            }
        }
    }
    out << dp[0][0];
}