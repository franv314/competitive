#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n + 1);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    long long diff = 0;
    for (int i = 0; i < n; i++)
        diff += abs(a[i] - b[i]);

    long long mi = 1e18;
    for (int i = 0; i < n; i++) {
        mi = min(mi, diff - abs(a[i] - b[i]) + abs(a[i] - b.back()) + abs(b.back() - b[i]) + 1);
        mi = min(mi, diff + 1 + abs(a[i] - b.back()));
        mi = min(mi, diff + 1 + abs(b[i] - b.back()));
    }

    cout << mi << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}