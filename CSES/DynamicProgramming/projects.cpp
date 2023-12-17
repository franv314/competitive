#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    
    vector<array<int, 3>> events;
    for (int i = 0; i < n; i++) {
        int a, b, p; cin >> a >> b >> p;
        events.push_back({b, a, p});
    }
    sort(events.begin(), events.end());
    map<int, long long, greater<int>> dp;
    dp[0] = 0;

    for (auto [b, a, p]: events) {
        dp[b] = max(dp.begin()->second, p + dp.upper_bound(a)->second);
    }

    cout << dp.begin()->second << '\n';
}