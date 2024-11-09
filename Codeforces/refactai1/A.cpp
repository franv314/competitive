#include <bits/stdc++.h>
using namespace std;

void solve() {
    int l, r, k; cin >> l >> r >> k;
    cout << max(r / k - l + 1, 0) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}