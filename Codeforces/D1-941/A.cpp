#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    
    sort(a.rbegin(), a.rend());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    a.push_back(0);

    int m = a.size() - 1;

    vector<int> dp(m + 1);

    dp[0] = false;

    for (int i = 1; i <= m; i++) {
        int diff = a[i - 1] - a[i];

        if (diff > 1) {
            dp[i] |= dp[i - 1];
        }
        dp[i] |= !dp[i - 1];
    }

    cout << (dp[m] ? "Alice\n" : "Bob\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}