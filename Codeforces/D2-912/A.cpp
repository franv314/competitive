#include <bits/stdc++.h>
using namespace std;
    
void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    
    bool ok = (k != 1) || is_sorted(a.begin(), a.end());
    cout << (ok ? "YES\n" : "NO\n");
}
    
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}