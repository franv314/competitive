#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, q; cin >> n >> k >> q;
    long long ans = 0;
    int curr_streak = 0;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        if (a > q) curr_streak = 0;
        else curr_streak++;
        
        ans += max(curr_streak - k + 1, 0);
    }
    cout << ans << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}