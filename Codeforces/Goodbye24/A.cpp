#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    for (int i = 0; i < n - 1; i++) {
        if (a[i] < 2 * a[i + 1] && a[i + 1] < 2 * a[i]) {
            return void(cout << "YES\n");
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
