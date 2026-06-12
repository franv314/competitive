#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    vector<bool> r(n - 1), c(m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i < n - 1 && grid[i][j] != grid[i + 1][j])
                r[i] = true;
            if (j < m - 1 && grid[i][j] != grid[i][j + 1])
                c[j] = true;
        }
    }

    cout << count(r.begin(), r.end(), true) + count(c.begin(), c.end(), true) << '\n';
}
