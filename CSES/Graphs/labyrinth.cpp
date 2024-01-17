#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<string> grid(n);

    pair<int, int> start, end;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        size_t pos_a = grid[i].find('A');
        size_t pos_b = grid[i].find('B');
    
        if (pos_a != string::npos) start = {i, pos_a};
        if (pos_b != string::npos) end = {i, pos_b};
    }

    vector<vector<bool>> visited(n, vector<bool>(m));
    vector<vector<char>> dir(n, vector<char>(m, '?'));

    queue<pair<int, int>> q;
    q.emplace(end.first, end.second);

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (visited[x][y]) continue;
        visited[x][y] = true;

        if (x > 0 && grid[x - 1][y] != '#' && !visited[x - 1][y]) {
            q.emplace(x - 1, y);
            dir[x - 1][y] = 'D';
        }
        if (x < n - 1 && grid[x + 1][y] != '#' && !visited[x + 1][y]) {
            q.emplace(x + 1, y);
            dir[x + 1][y] = 'U';
        }
        if (y > 0 && grid[x][y - 1] != '#' && !visited[x][y - 1]) {
            q.emplace(x, y - 1);
            dir[x][y - 1] = 'R';
        }
        if (y < m - 1 && grid[x][y + 1] != '#' && !visited[x][y + 1]) {
            q.emplace(x, y + 1);
            dir[x][y + 1] = 'L';
        }
    }

    if (!visited[start.first][start.second]) {
        cout << "NO\n";
        return 0;
    }

    auto [x, y] = start;
    string ans = "";
    while (end != make_pair(x, y)) {
        ans.push_back(dir[x][y]);
        switch (dir[x][y]) {
        case 'L': y--; break;
        case 'R': y++; break;
        case 'U': x--; break;
        case 'D': x++; break;
        }
    }

    cout << "YES\n";
    cout << ans.size() << '\n';
    cout << ans << '\n';
}