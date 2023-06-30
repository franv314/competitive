#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;
const int MAXM = 1000;

int solve() {
    int N, M;
    cin >> N >> M;

    int dp[MAXN + 1][MAXM + 2] = {};
    vector<int> V(N), G(M);

    for (int i=0; i<N; i++) {
        cin >> V[i];
    }
    for (int i=0; i<M; i++) {
        cin >> G[i];
    }
    G.push_back(-1);

    for (int n = N - 1; n >= 0; n--) {
        for (int m = M; m >= 0; m--) {
            dp[n][m] = max(1 + dp[n + 1][m], dp[n][m + 1]);
            if (V[n] < G[m]) dp[n][m] = max(dp[n][m], 2 + dp[n + 1][m + 1]);
        }
    }

    return dp[0][0];
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t;
    cin >> T;

    for (t = 1; t <= T; t++) {
        cout << "Case #" << t << ": " << solve() << endl;
    }
}
