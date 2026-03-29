#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    int cnt = (gcd(a[0], a[1]) != a[0]) + (gcd(a[n - 2], a[n - 1]) != a[n - 1]);
    for (int i = 1; i < n - 1; i++)
        cnt += lcm(gcd(a[i], a[i - 1]), gcd(a[i], a[i + 1])) <= a[i];

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
