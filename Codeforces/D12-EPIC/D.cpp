#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    map<int, int> freq;
    for (auto x: a) freq[x]++;

    sort(a.begin(), a.end());
    vector<int> vals = a;
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    vector<vector<int>> dp(vals.size() + 1, vector<int>(n + 1));
    for (int i = 0; i <= n; i++)
        dp[vals.size()][i] = 0;

    for (int i = vals.size() - 1; i >= 0; i--) {
        for (int m = 0; m < n; m++) {
            // i goes to A
            dp[i][m] = dp[i + 1][m + 1];

            // i goes to B
            if (m >= freq[vals[i]])
                dp[i][m] = max(dp[i][m], 1 + dp[i + 1][m - freq[vals[i]]]);
        }
    }

    cout << vals.size() - dp[0][0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}