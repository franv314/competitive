#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, q; cin >> n >> k >> q;
    vector<vector<int>> a(n, vector<int>(k));
    for (auto &row: a)
        for (auto &x: row)
            cin >> x;

    vector<vector<int>> b(k, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            b[j][i] = a[i][j];
    for (auto &row: b)
        for (int i = 1; i < n; i++)
            row[i] |= row[i - 1];

    while (q--) {
        int m; cin >> m;

        int l = 0, r = n;
        while (m--) {
            int R, c;
            char o;
            cin >> R >> o >> c;
            R--;

            if (o == '>') {
                l = max<int>(l, upper_bound(b[R].begin(), b[R].end(), c) - b[R].begin());
            } else {
                r = min<int>(r, lower_bound(b[R].begin(), b[R].end(), c) - b[R].begin());
            }
        }

        cout << (l < r ? l + 1 : -1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
}
