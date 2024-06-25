#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &x: grid) cin >> x;

    vector<int> row_score(n), col_score(m);
    vector<vector<bool>> visited(n, vector<bool>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            row_score[i] += grid[i][j] == '.';
            col_score[j] += grid[i][j] == '.';

            if (visited[i][j] || grid[i][j] == '.') continue;

            queue<pair<int, int>> q;
            vector<pair<int, int>> nodes;
            q.emplace(i, j);
            
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                if (visited[x][y] || grid[x][y] == '.') continue;
                
                visited[x][y] = true;
                nodes.emplace_back(x, y);

                if (x > 0) q.emplace(x - 1, y);
                if (x < n - 1) q.emplace(x + 1, y);
                if (y > 0) q.emplace(x, y - 1);
                if (y < m - 1) q.emplace(x, y + 1);
            }

            set<int> hor, ver;
            auto add_row = [&](int row) {
                if (row < 0 || row >= n || hor.count(row)) return;
                hor.insert(row);
                row_score[row] += nodes.size();
            };
            auto add_col = [&](int col) {
                if (col < 0 || col >= m || ver.count(col)) return;
                ver.insert(col);
                col_score[col] += nodes.size();
            };

            for (auto [x, y]: nodes) {
                add_row(x - 1); add_row(x); add_row(x + 1);
                add_col(y - 1); add_col(y); add_col(y + 1);
            }
        }
    }

    cout << max(*max_element(row_score.begin(), row_score.end()), *max_element(col_score.begin(), col_score.end())) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}