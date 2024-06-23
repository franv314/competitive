#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (auto &row: grid)
        for (auto &x: row)
            cin >> x;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int sus = -1e9;
            if (i > 0) sus = max(sus, grid[i - 1][j]);
            if (i < n - 1) sus = max(sus, grid[i + 1][j]);
            if (j > 0) sus = max(sus, grid[i][j - 1]);
            if (j < m - 1) sus = max(sus, grid[i][j + 1]);
            grid[i][j] = min(grid[i][j], sus);
        }
    }

    for (auto row: grid) {
        for (auto x: row) cout << x << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}