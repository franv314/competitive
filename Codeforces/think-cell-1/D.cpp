#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<int> ones;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ones.push_back(i);
        }
    }
    ones.push_back(n);
    ones.push_back(n + 1);
    ones.push_back(n + 2);

    vector<long long> dp(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            int next_one = *lower_bound(ones.begin(), ones.end(), i + 1);
            dp[i] = dp[next_one];
        } else {
            int next_one = *lower_bound(ones.begin(), ones.end(), i + 3);
            next_one = min(next_one, n);

            int cnt = n - next_one;
            dp[i] = dp[next_one] + cnt + next_one - i;
        }
    }

    cout << accumulate(dp.begin(), dp.end(), 0LL) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}