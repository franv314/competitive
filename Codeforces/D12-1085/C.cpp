#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    i64 n, h; cin >> n >> h;
    vector<i64> a(n);
    for (auto &x: a) cin >> x;

    vector<vector<i64>> by_start(n, vector<i64>(n));
    vector<vector<i64>> by_start_ps(n, vector<i64>(n + 1));

    for (int i = 0; i < n; i++) {
        i64 ma = -1e9;
        for (int j = i; j < n; j++) {
            ma = max(ma, a[j]);
            by_start[i][j] = h - ma;
        }
        ma = -1e9;
        for (int j = i; j >= 0; j--) {
            ma = max(ma, a[j]);
            by_start[i][j] = h - ma;
        }

        for (int j = 0; j < n; j++) {
            by_start_ps[i][j + 1] = by_start_ps[i][j] + by_start[i][j];
        }
    }

    i64 ans = h - a[0];
    for (int i = 0; i < n; i++) {
        pair<i64, i64> ma = {a[i], i};
        for (int j = i + 1; j < n; j++) {
            ma = max(ma, {a[j], j});
            i64 temp = by_start_ps[i][ma.second] - by_start_ps[i][0]
                     + by_start_ps[j][n] - by_start_ps[j][ma.second];
            ans = max(ans, temp);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
