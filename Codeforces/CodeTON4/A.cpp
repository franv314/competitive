#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        bool ok = false;
        for (int i = 1; i <= n; i++) {
            int x; cin >> x;
            if (x <= i) {
                ok = true;
            }
        }
        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }
}