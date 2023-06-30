#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int ans = 0;
    vector<int> a(n);
    for (auto &x: a) {
        cin >> x;
        if (x < 0) {
            ans = x;
        }
    }
    if (ans) cout << ans << '\n';
    else cout << *max_element(a.begin(), a.end()) << '\n';
}

int main() {
    // ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}