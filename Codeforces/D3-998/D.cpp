#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    for (int i = 0; i < n - 1; i++) {
        if (a[i + 1] < a[i])
            return void(cout << "NO\n");
        a[i + 1] -= a[i];
    }

    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
