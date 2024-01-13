#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    sort(a.rbegin(), a.rend());

    vector<int> ps(n + 1);
    for (int i = 0; i < n; i++) ps[i + 1] = ps[i] + a[i];

    int ans = -1e9;

    for (int rem = 0; rem <= k; rem++) {
        int flip = min(x, n - rem);
        int score = (ps[n] - ps[rem + flip]) - (ps[rem + flip] - ps[rem]);

        ans = max(ans, score);
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}