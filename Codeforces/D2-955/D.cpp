#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &row: a)
        for (auto &el: row)
            cin >> el;
    vector<string> grid(n);
    for (auto &row: grid)
        cin >> row;

    vector<vector<long long>> ps(n + 1, vector<long long>(m + 1));
    long long diff = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1') {
                diff += a[i][j];
                ps[i + 1][j + 1] = ps[i + 1][j] + ps[i][j + 1] - ps[i][j] + 1;
            } else {
                diff -= a[i][j];
                ps[i + 1][j + 1] = ps[i + 1][j] + ps[i][j + 1] - ps[i][j] - 1;
            }
        }
    }

    diff = abs(diff);
    long long g = 0;
    for (int i = 0; i <= n - k; i++) {
        for (int j = 0; j <= m - k; j++) {
            int d = ps[i + k][j + k] - ps[i][j + k] - ps[i + k][j] + ps[i][j];
            g = gcd(g, abs(d));
        }
    }

    if (diff == 0) cout << "YES\n";
    else if (g == 0) cout << "NO\n";
    else if (diff % g == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}