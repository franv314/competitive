#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    long long a, b; cin >> a >> b;

    // This DP just computes powers of 9...
    vector<vector<long long>> dp(19, vector<long long>(10));
    fill(dp[0].begin(), dp[0].end(), 1);

    for (int p = 1; p < 19; p++) {
        for (int d = 0; d <= 9; d++) {
            dp[p][d] = accumulate(dp[p - 1].begin(), dp[p - 1].end(), 0ll) - dp[p - 1][d];
        }
    }

    auto count = [&](long long r) {
        if (r == -1) return 0ll;
        if (r == 0) return 1ll;

        string num = to_string(r);
        reverse(num.begin(), num.end());
        num.push_back('0');

        int dup = 0;
        for (int i = 0; i < num.size() - 1; i++) {
            if (num[i] == num[i + 1]) dup = i;
        }

        long long cnt = dup == 0;
        for (; dup < num.size() - 1; dup++) {
            cnt += accumulate(dp[dup].begin(), dp[dup].begin() + num[dup] - '0', 0ll);
            if (num[dup + 1] < num[dup] || (dup == 0 && num[dup + 1] == num[dup]))
                cnt -= dp[dup][num[dup + 1] - '0'];
        }

        for (int sz = 0; sz < num.size() - 2; sz++) {
            cnt += accumulate(dp[sz].begin() + 1, dp[sz].end(), 0ll);
        }
        cnt++;

        return cnt;
    };

    cout << count(b) - count(a - 1) << '\n';
}