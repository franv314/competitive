#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int m; cin >> m;
    vector<int> b(m);
    for (auto &x: b) cin >> x;
    int x, y; cin >> x >> y;
    int n; cin >> n;
    vector<int> r(n), c(n);
    for (int i = 0; i < n; i++) cin >> r[i] >> c[i];

    sort(b.begin(), b.end());
    vector<vector<int>> times(m);

    for (int i = 0; i < n; i++) {
        int nxt = lower_bound(b.begin(), b.end(), c[i]) - b.begin();
        if (nxt == m) {
            times[nxt - 1].push_back(r[i] + abs(c[i] - b[nxt - 1]));
        } else if (nxt == 0) {
            times[nxt].push_back(r[i] + abs(c[i] - b[nxt]));
        } else if (c[i] - b[nxt - 1] <= b[nxt] - c[i]) {
            times[nxt - 1].push_back(r[i] + abs(c[i] - b[nxt - 1]));
        } else {
            times[nxt].push_back(r[i] + abs(c[i] - b[nxt]));
        }
    }

    for (auto &arr: times) sort(arr.begin(), arr.end());

    int ans = 1e9;
    for (int i = 0; i < m; i++) {
        int time = x + abs(y - b[i]);
        ans = min(ans, int(upper_bound(times[i].begin(), times[i].end(), time) - times[i].begin()));
    }

    cout << ans << '\n';
}