#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int l = 1;
    for (int i = 0; i < n - 1; i++) {
        l = lcm(l, a[i] / gcd(a[i], a[i + 1]));
    }

    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
