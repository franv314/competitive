#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    
    vector<vector<int>> grid(n, vector<int>(n, -1));
    int count = 0;
    if (n % 2)
        grid[n / 2][n / 2] = count++;
    for (int layer = n / 2 - 1; layer >= 0; layer--) {
        for (int y = layer + 1; y < n - layer; y++)
            grid[layer][y] = count++;
        for (int x = layer + 1; x < n - layer; x++)
            grid[x][n - layer - 1] = count++;
        for (int y = n - layer - 2; y >= layer; y--)
            grid[n - layer - 1][y] = count++;
        for (int x = n - layer - 2; x >= layer; x--)
            grid[x][layer] = count++;
    }

    for (auto row: grid) {
        for (auto el: row)
            cout << el << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
