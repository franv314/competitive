#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    if (k > 30) cout << 1 + n << '\n';
    else cout << min(1 + n, 1 << k) << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}