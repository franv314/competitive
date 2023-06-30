#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, x; cin >> n >> k >> x;
    if (x != 1) {
        cout << "YES\n" << n << '\n';
        for (int i = 0; i < n; i++) cout << "1 ";
        cout << '\n';
        return;
    }
    if (k == 1) {
        cout << "NO\n";
        return;
    }
    if (k == 2) {
        if (n % 2 == 0) {
            cout << "YES\n" << n / 2 << '\n';
            for (int i = 0; i < n; i += 2) cout << "2 ";
            cout << '\n';
        } else {
            cout << "NO\n";
        }
        return;
    }
    if (n == 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n" << n / 2 << '\n';
    if (n % 2 == 1) {
        n -= 3;
        cout << "3 ";
    }
    for (int i = 0; i < n; i += 2) cout << "2 ";
    cout << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}