#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &x: grid) cin >> x;

    int l = 1e9, r = -1e9, t = 1e9, b = -1e9;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                l = min(l, j);
                r = max(r, j);
                t = min(t, i);
                b = max(b, i);
            }
        }
    }

    cout << (t + b) / 2 + 1 << " " << (l + r) / 2 + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}