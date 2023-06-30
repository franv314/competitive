#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &x: a) cin >> x;

        bool ok = false;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (__gcd(a[i], a[j]) <= 2) {
                    ok = true;
                }
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
}