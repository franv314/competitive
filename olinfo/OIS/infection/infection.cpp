#include <bits/stdc++.h>
using namespace std;

int N, M;

pair<int, int> new_coords(int x, int y) {
    return {x + y, y - x + N};
}

int main() {
    cin >> N >> M;
    vector<vector<int>> grid(N + M, vector<int>(N + M));
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            auto [x, y] = new_coords(n, m);
            cin >> grid[x][y];
        }
    }

    vector<vector<long long>> ps(N + M + 1, vector<long long>(N + M + 1));
    for (int i = 1; i <= N + M; i++) {
        for (int j = 1; j <= N + M; j++) {
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + grid[i - 1][j - 1];
        }
    }
    
    long long curr = 0;
    pair<int, int> ans;
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            auto [x, y] = new_coords(n, m);

            int dst = min({n, m, N - n - 1, M - m - 1});

            // Sum over [x - dst, x + dst] * [y - dst, y + dst]
            long long total = 
                + ps[x + dst + 1][y + dst + 1] 
                - ps[x - dst][y + dst + 1]
                - ps[x + dst + 1][y - dst] 
                + ps[x - dst][y - dst];
            if (total > curr) {
                curr = total;
                ans = {n, m};
            }
        }
    }
    cout << ans.first << " " << ans.second << "\n";
}