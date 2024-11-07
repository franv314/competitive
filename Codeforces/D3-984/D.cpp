#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;
    
    int cnt = 0;
    for (int layer = 0; layer < min(n, m) / 2; layer++) {
        string l = "";

        for (int _: {0, 1}) {
            for (int i = layer; i < m - layer - 1; i++)
                l += grid[layer][i];
            for (int i = layer; i < n - layer - 1; i++)
                l += grid[i][m - layer - 1];
            for (int i = m - layer - 1; i > layer; i--)
                l += grid[n - layer - 1][i];
            for (int i = n - layer - 1; i > layer; i--)
                l += grid[i][layer];
        }

        l.resize(l.size() / 2 + 3);
        for (int i = 0; i < l.size() - 3; i++)
            cnt += l.substr(i, 4) == "1543";
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
