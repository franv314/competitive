#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a1, a2, a4, a5; cin >> a1 >> a2 >> a4 >> a5;
    map<int, int> f;
    f[a1 + a2]++;
    f[a4 - a2]++;
    f[a5 - a4]++;

    cout << max({f[a1 + a2], f[a4 - a2], f[a5 - a4]}) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
