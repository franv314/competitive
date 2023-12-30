#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b; cin >> a >> b;
    int l = lcm(a, b);

    if (l != b) cout << l << '\n';
    else cout << b * (b / a) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}