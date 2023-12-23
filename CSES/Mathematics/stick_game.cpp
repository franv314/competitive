#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> p(k);
    for (auto &x: p) cin >> x;

    vector<int> dp(n + 1);
    vector<int> mex(k + 1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        fill(mex.begin(), mex.end(), 1);
        for (auto x: p) {
            if (x <= i) mex[dp[i - x]] = 0;
        }
        dp[i] = find(mex.begin(), mex.end(), 1) - mex.begin();
    }

    for (int i = 1; i <= n; i++) {
        cout << (dp[i] ? 'W' : 'L');
    }
    cout << '\n';
}