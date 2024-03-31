#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<int> K(N);
    for (auto &k: K) cin >> k;

    vector<int> act_k;
    int seq_start = -1, seq_last = -1;

    for (int i = 0; i < N; i++) {
        int cur = K[i];
        int nxt = i == N - 1 ? M : K[i + 1];

        if (cur != seq_last + 1) {
            act_k.push_back(cur);
            seq_start = seq_last = cur;
        } else {
            seq_last = cur;

            if (nxt != cur + 1 || (cur & 1) == (seq_start & 1)) {
                act_k.push_back(cur);
            }
        }
    }

    auto get_cost = [&](int l, int r) {
        return (r == act_k.size() ? M : act_k[r]) - (l == 0 ? -1 : act_k[l - 1]) - 1;
    };

    vector<vector<int>> dp(act_k.size() + 1);
    for (int i = 0; i <= act_k.size(); i++) {
        dp[i].resize(act_k.size() + 1 - i);
        dp[i][0] = 0;
    }

    for (int i = act_k.size(); i >= 0; i--) {
        for (int j = i + 1; j <= act_k.size(); j++) {
            dp[i][j - i] = INT_MAX;

            for (int k = i; k < j; k++) {
                dp[i][j - i] = min(dp[i][j - i], dp[i][k - i] + dp[k + 1][j - k - 1]);
            }

            dp[i][j - i] += get_cost(i, j);
        }
    }

    cout << dp[0][act_k.size()] << '\n';
}