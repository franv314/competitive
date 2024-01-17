#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    vector<vector<bool>> visited(n, vector<bool>(m));
    int cc = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visited[i][j] || grid[i][j] == '#') continue;
            
            cc++;
            queue<pair<int, int>> q;
            q.emplace(i, j);
            
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                if (visited[x][y] || grid[x][y] == '#') continue;
                visited[x][y] = true;

                if (x > 0) q.emplace(x - 1, y);
                if (x < n - 1) q.emplace(x + 1, y);    
                if (y > 0) q.emplace(x, y - 1);
                if (y < m - 1) q.emplace(x, y + 1);    
            }
        }
    }

    cout << cc << '\n';
}