#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> b(n - 1);
    for (auto &x: b) cin >> x;

    vector<int> a(n);
    for (int i = 0; i < n - 1; i++) {
        a[i] |= b[i];
        a[i + 1] |= b[i];
    }

    for (int i = 0; i < n - 1; i++) {
        if ((a[i] & a[i + 1]) != b[i])
            return void(cout << "-1\n");
    }

    for (auto x: a)
        cout << x << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--)
        solve();
}