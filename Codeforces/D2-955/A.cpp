#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x0, y0; cin >> x0 >> y0;
    int x1, y1; cin >> x1 >> y1;

    if ((x0 < y0) != (x1 < y1)) cout << "NO\n";
    else cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}