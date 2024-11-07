#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, m, r, c; cin >> n >> m >> r >> c;

    long long ans = (n - r) * (m - 1) + (n * m - (r - 1) * m - c);
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}