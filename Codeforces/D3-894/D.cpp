#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n; cin >> n;

    int64_t l = 0, r = 2e9;
    while (l + 1 < r) {
        int64_t m = (l + r) / 2;
        
        if (m * (m - 1) / 2 > n) r = m;
        else l = m;
    }

    cout << l + n - l * (l - 1) / 2 << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}