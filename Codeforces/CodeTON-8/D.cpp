#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> value(n, vector<int>(n + 1));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> value[i][j];
        }
    }

    vector<priority_queue<long long>> dp(n + 2);
    dp[n].push(0);
    dp[n + 1].push(0);
    for (int i = 1; i < k; i++) {
        dp[n].push(-1e18);
        dp[n + 1].push(-1e18);
    }

    for (int i = n - 1; i >= 0; i--) {
        priority_queue<pair<long long, int>> tops;
        for (int j = i + 1; j <= n + 1; j++) {
            tops.emplace(dp[j].top() + value[i][j - 1], j);
        }

        vector<pair<long long, int>> repush;

        for (int j = 0; j < k; j++) {
            auto [val, idx] = tops.top(); tops.pop();
            dp[i].push(val);

            dp[idx].pop();
            repush.emplace_back(val - value[i][idx - 1], idx);

            tops.emplace(dp[idx].top() + value[i][idx - 1], idx);
        }

        for (auto [val, idx]: repush) dp[idx].push(val);
    }

    while (!dp[0].empty()) {
        cout << dp[0].top() << ' ';
        dp[0].pop();
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}