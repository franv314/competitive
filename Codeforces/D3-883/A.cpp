#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int ans = 0;
    while (n--) {
        int a, b; cin >> a >> b;
        ans += (a > b);
    }
    cout << ans << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}