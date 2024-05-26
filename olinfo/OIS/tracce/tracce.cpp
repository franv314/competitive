#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

signed main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N; in >> N;
    string S; in >> S;

    vector<int> dp(N + 1);
    dp[0] = 1;
    int dpsum = 1;
    int pow9 = 1;
    int pow10 = 1;
    for (int len = 1; len <= N; len++) {
        pow10 = 10LL * pow10 % MOD;
        pow9 = 9LL * pow9 % MOD;
        dp[len] = (dpsum + pow9) % MOD;

        dpsum = 9LL * dpsum % MOD;
        dpsum = (dpsum + dp[len]) % MOD;
        if (len >= S.size() - 1) dpsum = (dpsum - dp[len - S.size() + 1] + MOD) % MOD;
    }

    if (S.size() == 1) out << (pow10 - pow9 + MOD) % MOD << '\n';
    else out << (pow10 - dp[N] + MOD) % MOD << '\n';
}