#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    
    sort(a.begin(), a.end());
    int ans = 1e9;

    for (int st = 0; st < n - 1; st++) {
        int sum = a[st] + a[st + 1];
        int ok = lower_bound(a.begin(), a.end(), sum) - (a.begin() + st);

        ans = min(ans, n - ok);
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
