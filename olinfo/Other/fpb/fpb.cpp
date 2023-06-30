#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define _ << " " <<

const int MOD = 1e9 + 7;
const int MAXN = 5e4;
const int MAXK = 20;

int N, K;
vector<int> A;

long long dp[MAXN + 1][MAXK + 1];
long long ps[MAXN + 2][MAXK + 1];

void read_input() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    A.resize(N);
    for (int n = 0; n < N; n++)
        cin >> A[n];
}

void populate_dp() {
    for (int i = 0; i <= N; i++) {
        dp[i][0] = 1;
        ps[i + 1][0] = i + 1;
    }
    for (int k = 1; k <= K; k++) {
        for (int n = 1; n <= N; n++) {
            dp[n][k] = (dp[n - 1][k] + ps[n][k - 1]) % MOD;
            ps[n + 1][k] = (ps[n][k] + dp[n][k]) % MOD;
        }
    }
}

long long count(int s, int l, int r) {
    long long total = 0;
    for (int k = 0; k < K; k++) {
        total = (total + (ps[N - l][K - 1 - k] - ps[N - r][K - 1 - k] + MOD) * dp[s][k]) % MOD;
    }
    return total;
}

long long solve() {
    long long tot = 0;
    list<int> decreasing;
    for (int i = N - 1; i >= 0; i--) {
        long long old = i;
        decreasing.push_front(i);

        int g = A[i];
        for (auto it = next(decreasing.begin()); it != decreasing.end(); it++) {
            int ng = __gcd(g, A[*it]);
            if (ng == g) {
                it--;
                decreasing.erase(next(it));
            } else {
                tot = (tot + g * count(i, old, *it)) % MOD;
                g = ng;
                old = *it;
            }
        }
        tot = (tot + g * count(i, old, N)) % MOD;
    }
    return tot;
}

int main() {
    read_input();
    populate_dp();
    
    cout << solve() << endl;

    return 0;
}