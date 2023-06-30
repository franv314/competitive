#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> inverted(n);

    for (int i = 2; i < n; i++) {
        inverted[i] = inverted[i - 1];
        if (a[i - 2] >= a[i - 1] && a[i - 1] >= a[i]) {
            inverted[i]++;
        }
    }

    while (q--) {
        int l, r; cin >> l >> r;
        l--;

        int ans = r - l;
        if (r - l > 2) ans -= inverted[r - 1] - inverted[l + 1];
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    solve();
}