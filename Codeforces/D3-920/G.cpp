#include <bits/stdc++.h>
using namespace std;

int solve_rotation(int n, int m, int k, const vector<string> &grid) {
    vector<vector<int>> ps_hor(n + 1, vector<int>(m + 1));
    vector<vector<int>> ps_diag1(n + 1, vector<int>(m + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ps_hor[i + 1][j + 1]
                = ps_hor[i][j + 1] + ps_hor[i + 1][j] - ps_hor[i][j] + (grid[i][j] == '#');
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ps_diag1[i + 1][j + 1]
                = ps_diag1[i][j] + ps_diag1[i][j + 1] - (i > 0 ? ps_diag1[i - 1][j] : 0) + (grid[i][j] == '#');  
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j + k - 1 <= m) {
                int t = ps_hor[i][j + k - 1] - ps_hor[i][j - 1] - ps_diag1[i - 1][j + k - 1];
                if (i - k - 1 >= 0) t += ps_diag1[i - k - 1][j - 1];

                ans = max(ans, t);
            } else {
                int up = j + k - m;
                int t = ps_hor[i][m] - ps_hor[i][j - 1];

                if (i - up >= 0) t -= ps_diag1[i - up][m];
                if (i - k - 1 >= 0) t += ps_diag1[i - k - 1][j - 1];

                ans = max(ans, t);
            }
        }
    }

    return ans;
} 

void solve() {
    int n, m, k; cin >> n >> m >> k;
    k++;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    vector<string> grid1 = grid;
    vector<string> grid2 = grid;
    reverse(grid2.begin(), grid2.end());
    for (auto &x: grid2) reverse(x.begin(), x.end());

    vector<string> grid3(m, string(n, ' '));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid3[j][n - 1 - i] = grid[i][j];
        }
    }
    vector<string> grid4 = grid3;
    reverse(grid4.begin(), grid4.end());
    for (auto &x: grid4) reverse(x.begin(), x.end());

    int ans1 = solve_rotation(n, m, k, grid1);
    int ans2 = solve_rotation(n, m, k, grid2);
    int ans3 = solve_rotation(m, n, k, grid3);
    int ans4 = solve_rotation(m, n, k, grid4);

    cout << max({ans1, ans2, ans3, ans4}) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}