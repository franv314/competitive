#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int old; cin >> old;

    bool ok = true;
    for (int i = 1; i < n; i++) {
        int x; cin >> x;
        if (abs(x - old) != 5 && abs(x - old) != 7) {
            ok = false;
        }
        old = x;
    }

    cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
