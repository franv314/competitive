#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y; cin >> x >> y;
    int v = abs(x - y);

    int ans = v == 0;
    for (int i = 1; i <= v; i++)
        ans += v % i == 0;
    
    cout << ans << '\n';
    for (int i = 0; i < x; i++) cout << "1 ";
    for (int i = 0; i < y; i++) cout << "-1 ";
    cout << '\n';\
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
