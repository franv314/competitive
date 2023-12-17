#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto &c: a) cin >> c;
    
    vector<int> dp(x + 1);
    dp[0] = 0;

    for (int i = 1; i <= x; i++) {
        int mi = 1e9;
        for (auto c: a) {
            if (i - c < 0) continue;
            mi = min(mi, 1 + dp[i - c]);
        }
        dp[i] = mi;
    }
    cout << (dp[x] == 1e9 ? -1 : dp[x]) << '\n';
}