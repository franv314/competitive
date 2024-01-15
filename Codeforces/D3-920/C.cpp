#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, f, a, b; cin >> n >> f >> a >> b;
    vector<int> m(n);
    for (auto &x: m) cin >> x;

    int last = 0;
    for (auto x: m) {
        f -= min((long long)a * (x - last), 1ll * b);
        if (f <= 0) return void(cout << "NO\n");
        last = x;
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}