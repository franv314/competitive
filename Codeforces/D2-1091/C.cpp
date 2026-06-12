#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, a, b; cin >> n >> m >> a >> b;
    bool ok = gcd(a, n) == 1 && gcd(b, m) == 1 && gcd(n, m) <= 2;

    cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
