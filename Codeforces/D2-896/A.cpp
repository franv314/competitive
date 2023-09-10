#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
    }

    if (n % 2 == 0) {
        cout << "2\n";
        cout << 1 << " " << n << "\n";
        cout << 1 << " " << n << "\n";
    } else {
        cout << "4\n";
        cout << 1 << " " << n << "\n";
        cout << 1 << " " << n - 1 << "\n";
        cout << n - 1 << " " << n << "\n";
        cout << n - 1 << " " << n << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}