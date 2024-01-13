#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int points = 0;
    for (int k = 1; k <= n; k++) {
        if (n % k) continue;
        int g = 0;
        for (int i = 0; i < n - k; i++) {
            if (a[i + k] != a[i]) {
                g = gcd(g, abs(a[i + k] - a[i]));
            }
        }

        if (g == 0 || g >= 2) points++;
    }

    cout << points << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}