#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    if (n % k) {
        cout << 1 << "\n";
        cout << n << "\n";
    } else {
        cout << 2 << "\n";
        cout << -1 << " " << n + 1 << "\n";
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}