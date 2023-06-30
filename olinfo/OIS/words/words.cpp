#include <bits/stdc++.h>
using namespace std;

#define MAXL 10'002
#define INF (long long)1e18

long long N, skipped;
int L, K;

vector<int> allowed[27][27];
optional<long long> dp[MAXL][27][27];

long long recursive(int len, int old1, int old2) {
    if (len == L) {
        dp[len][old1][old2] = 1;
        return 1;
    }

    long long total = 0;

    for (auto next: allowed[old1][old2]) {
        long long count = dp[len + 1][old2][next].value_or(recursive(len + 1, old2, next));    

        if (total >= INF || count >= INF) total = INF;
        else total += count;
    }
    dp[len][old1][old2] = total;
    return total;
}

void ans(int len, int old1, int old2) {
    if (len == L) return;

    for (auto next: allowed[old1][old2]) {
        if (skipped + dp[len + 1][old2][next].value() >= N) {
            cout << (char)(next + 'a');
            return ans(len + 1, old2, next);
        }
        skipped += dp[len + 1][old2][next].value();
    }
}

int main() {
    cin >> N;
    cin >> L >> K;
    
    for (int i = 0; i < K; i++) {
        char a, b, c; cin >> a >> b >> c;
        allowed[a - 'a'][b - 'a'].push_back(c - 'a');
    }

    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 26; j++) {
            allowed[26][i].push_back(j);
        }
    }

    recursive(0, 26, 26);
    ans(0, 26, 26);
}