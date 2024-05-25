#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    sort(a.begin(), a.end());
    int x = a[0], y = -1;

    for (int i = 1; i < n; i++) {
        if (a[i] % x == 0) continue;
        if (y == -1) {
            y = a[i];
            continue;
        }
        if (a[i] % y == 0) continue;
        return void(cout << "No\n");
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}