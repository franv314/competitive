#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &x: grid) cin >> x;

    vector<vector<int>> score(n + 1, vector<int>(m + 1, 0));
    vector<vector<bool>> visited(n, vector<bool>(m));

    vector<int> row_count(n), col_count(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            row_count[i] += grid[i][j] == '.';
            col_count[j] += grid[i][j] == '.';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int pt = row_count[i] + col_count[j] - (grid[i][j] == '.');
            score[i][j] += pt;
            score[i + 1][j + 1] += pt;
            score[i + 1][j] -= pt;
            score[i][j + 1] -= pt;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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

            int l = 1e9, r = -1e9, t = 1e9, b = -1e9;
            for (auto [x, y]: nodes) {
                l = min(l, y - 1);
                r = max(r, y + 1);
                t = min(t, x - 1);
                b = max(b, x + 1);
            }
            l = max(l, 0);
            r = min(r, m - 1);
            t = max(t, 0);
            b = min(b, n - 1);

            score[t][0] += nodes.size();
            score[b + 1][m] += nodes.size();
            score[t][m] -= nodes.size();
            score[b + 1][0] -= nodes.size();

            score[0][l] += nodes.size();
            score[n][r + 1] += nodes.size();
            score[n][l] -= nodes.size();
            score[0][r + 1] -= nodes.size();

            score[t][l] -= nodes.size();
            score[b + 1][r + 1] -= nodes.size();
            score[t][r + 1] += nodes.size();
            score[b + 1][l] += nodes.size();
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            score[i][j] += score[i - 1][j];
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            score[j][i] += score[j][i - 1];
        }
    }

    int ma = -1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            ma = max(ma, score[i][j]);
        }
    }

    cout << ma << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}