#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;

    if (m == 1) {
        cout << 0 << '\n';
        for (int i = 0; i < n; i++) {
            cout << 0 << '\n';
        }
        return;
    }

    int s = min(n + 1, m);

    vector<vector<int>> grid(n, vector<int>(m));
    for (int v = 0; v < s; v++) {
        for (int r = 0; r < s - 1; r++) {
            int c = (v + r) % s;
            grid[r][c] = v;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = s; j < m; j++) {
            grid[i][j] = j;
        }
    }

    for (int i = s - 1; i < n; i++) {
        grid[i] = grid[i % (s - 1)];
    }

    cout << s << '\n';
    for (auto row: grid) {
        for (auto cell: row) {
            cout << cell << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}