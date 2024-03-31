#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, K; cin >> N >> K;
    vector<int> X(N);
    for (auto &x: X) cin >> x;

    vector<int> diffs;
    for (int i = 0; i < N - 1; i++)
        diffs.push_back(X[i + 1] - X[i]);

    sort(diffs.begin(), diffs.end());
    
    int l = 0, r = diffs.size();
    while (l + 1 < r) {
        int m = (l + r) / 2;

        vector<int> dp(K + 1);
        dp[0] = true;

        int fst = 0;
        for (int i = 1; i < N; i++) {
            if (X[i] - X[i - 1] < diffs[m]) continue;

            for (int j = K; j >= i - fst; j--)
                dp[j] |= dp[j - i + fst];

            fst = i;
        }
        for (int j = K; j >= N - fst; j--)
            dp[j] |= dp[j - N + fst];

        if (dp[K]) l = m;
        else r = m;
    }

    cout << diffs[l] << '\n';
}