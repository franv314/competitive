#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    bool has_even = false, has_odd = false;
    for (auto x: a) {
        if (x & 1) has_odd = true;
        else has_even = true;
    }

    if (has_even && has_odd) {
        return void(cout << "-1\n");
    }

    cout << "31\n";
    for (int i = 29; i >= 0; i--) {
        cout << (1 << i) << ' ';
        for (auto &x: a)
            x = abs(x - (1 << i));
    }

    cout << a[0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--)
        solve();
}