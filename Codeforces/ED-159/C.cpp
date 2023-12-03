#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    sort(a.begin(), a.end());
    int g = 0;
    for (int i = 0; i < n - 1; i++) {
        g = gcd(g, a.back() - a[i]);
    }

    long long s = (long long)a.back() * n - accumulate(a.begin(), a.end(), 0LL);

    int last = a.back();
    while (binary_search(a.begin(), a.end(), last)) last -= g;

    cout << (s + a.back() - last) / g << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}