#include <bits/stdc++.h>
using namespace std;

#define MAXN 500
#define MAXH 2002

int dp[MAXN][MAXH][2];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> H(N);
    for (auto &h: H) {
        cin >> h;
        h++;
    }

    for (int h = 0; h < MAXH; h++) {
        dp[N - 1][h][0] = dp[N - 1][h][1] = (H[N - 1] - h) * (H[N - 1] - h);
    }

    for (int i = N - 2; i >= 0; i--) {
        dp[i][0][0] = 2e9 + 1;
        dp[i][MAXH - 1][1] = 2e9 + 1;

        int best = 2e9 + 1;
        for (int h = 1; h < MAXH; h++) {
            best = min(best, dp[i + 1][h - 1][1]);
            dp[i][h][0] = best + (H[i] - h) * (H[i] - h);
        }

        best = 2e9 + 1;
        for (int h = MAXH - 2; h >= 0; h--) {
            best = min(best, dp[i + 1][h + 1][0]);
            dp[i][h][1] = best + (H[i] - h) * (H[i] - h);
        }
    }

    int ans = 2e9 + 1;
    for (int h = 0; h < MAXH; h++) {
        ans = min({ans, dp[0][h][0], dp[0][h][1]});
    }

    cout << ans << '\n';
}