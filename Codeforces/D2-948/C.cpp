#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    sort(a.begin(), a.end());

    long long l = 1;
    for (auto x: a) {
        l = lcm(l, x);
        if (l > a.back()) {
            cout << n << '\n';
            return;
        }
    }

    if (l != a.back()) {
        cout << n << '\n';
        return;
    }

    map<int, int> dp;
    dp[1] = 0;

    for (auto x: a) {
        vector<pair<int, int>> new_dps;
        for (auto [l, len]: dp) {
            new_dps.emplace_back(lcm(l, x), len + 1);
        }
        for (auto [l, len]: new_dps) {
            dp[l] = max(dp[l], len);
        }
    }

    int best = 0;
    for (auto x: a) {
        for (auto [l, len]: dp) {
            if (!binary_search(a.begin(), a.end(), l))
                best = max(best, len);
        }
    }

    cout << best << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}