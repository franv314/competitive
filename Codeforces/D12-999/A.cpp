#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int odd = 0, even = 0;
    for (auto x: a) {
        if (x & 1) odd++;
        else even++;
    }

    if (even != 0)
        cout << 1 + odd << '\n';
    else
        cout << odd - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
