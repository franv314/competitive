#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void solve() {
    int N, M, K; cin >> N >> M >> K;
    vector<string> grid(N);
    for (auto &row: grid) cin >> row;

    vector<optional<pair<int, int>>> tunnels(K);
    map<pair<int, int>, pair<int, int>> tunnels2;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ('0' <= grid[i][j] && grid[i][j] <= '9') {
                if (tunnels[grid[i][j] - '0'].has_value()) {
                    tunnels2[tunnels[grid[i][j] - '0'].value()] = {i, j};
                    tunnels2[{i, j}] = tunnels[grid[i][j] - '0'].value();
                } else {
                    tunnels[grid[i][j] - '0'] = {i, j};
                }
            }
        }
    }

    vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(1 << K)));
    vector<int> bitmasks(1 << K);
    iota(bitmasks.begin(), bitmasks.end(), 0);
    sort(bitmasks.begin(), bitmasks.end(), [&](int a, int b) { return __popcount(a) < __popcount(b); });

    for (auto mask: bitmasks) dp[N - 1][M - 1][mask] = 1;

    for (auto mask: bitmasks) {
        for (int x = N - 1; x >= 0; x--) {
            for (int y = M - 1; y >= 0; y--) {
                if (x != N - 1) {
                    if ('0' <= grid[x + 1][y] && grid[x + 1][y] <= '9' && (mask & (1 << (grid[x + 1][y] - '0')))) {
                        int new_mask = mask & ~(1 << (grid[x + 1][y] - '0'));
                        auto [new_x, new_y] = tunnels2[{x + 1, y}];
                        (dp[x][y][mask] += dp[new_x][new_y][new_mask]) %= MOD;
                    } else if (grid[x + 1][y] == '.'){
                        (dp[x][y][mask] += dp[x + 1][y][mask]) %= MOD;
                    }
                }
                if (y != M - 1) {
                    if ('0' <= grid[x][y + 1] && grid[x][y + 1] <= '9' && (mask & (1 << (grid[x][y + 1] - '0')))) {
                        int new_mask = mask & ~(1 << (grid[x][y + 1] - '0'));
                        auto [new_x, new_y] = tunnels2[{x, y + 1}];
                        (dp[x][y][mask] += dp[new_x][new_y][new_mask]) %= MOD;
                    } else if (grid[x][y + 1] == '.') {
                        (dp[x][y][mask] += dp[x][y + 1][mask]) %= MOD;
                    }
                }
            }
        }
    }
    cout << dp[0][0][(1 << K) - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
}