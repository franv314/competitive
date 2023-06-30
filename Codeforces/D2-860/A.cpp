#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        for (int i = 0; i < n - 1; i++) {
            if (!((a[i] <= a.back() && b[i] <= b.back()) || (b[i] <= a.back() && a[i] <= b.back()))) {
                cout << "NO\n";
                goto next;
            }
        }
        cout << "YES\n";
        next:;
    }
}