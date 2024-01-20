#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, K; cin >> N >> K;
    vector<int> T(N);
    for (auto &x: T) cin >> x;

    int M; cin >> M;
    vector<set<int>> ok(K + 1);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        ok[u].insert(v);
    }

    vector<int> dp(N + 1, -1e9);
    dp[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (T[i] == K + 1) continue;
        if (i + 1 == N || (i + 1 < N && ok[T[i]].count(T[i + 1]))) dp[i] = max(dp[i], 1 + dp[i + 1]);
        if (i + 2 == N || (i + 2 < N && ok[T[i]].count(T[i + 2]))) dp[i] = max(dp[i], 1 + dp[i + 2]);
    }

    cout << max({dp[0], dp[1], 0}) << '\n';
}