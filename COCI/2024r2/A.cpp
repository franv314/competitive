#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;

    vector<string> grid(n);
    for (auto &x: grid) cin >> x;

    int ma = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '+') continue;
            int size = 0;

            for (int k = 1; ; k++) {
                if (i + k >= n || grid[i + k][j] != '|') break;
                if (i - k < 0 || grid[i - k][j] != '|') break;
                if (j + k >= m || grid[i][j + k] != '-') break;
                if (j - k < 0 || grid[i][j - k] != '-') break;
                if (grid[i + k][j + k] != '\\') break;
                if (grid[i - k][j - k] != '\\') break;
                if (grid[i + k][j - k] != '/') break;
                if (grid[i - k][j + k] != '/') break;
                size++;
            }

            ma = max(ma, size);
        }
    }

    cout << ma << '\n';
}