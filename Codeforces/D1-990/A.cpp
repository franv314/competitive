#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    long long ma = -1e18;
    for (int i = 0; i < n; i++) {
        long long ans = 0;
        for (int j = 0; j < n; j++) {
            ans += max(a[j], b[j]);
            if (i == j)
                ans += min(a[j], b[j]);
        }

        ma = max(ma, ans);
    }

    cout << ma << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
