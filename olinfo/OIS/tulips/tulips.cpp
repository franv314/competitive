#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int N, K; cin >> N >> K;
    vector<int> A(N);
    for (auto &x: A) cin >> x;

    vector<i64> old_dp(N + 1, -1e18);
    vector<i64> dp(N + 1);
    old_dp[N] = 0;

    for (int _ = 1; _ <= K; _++) {
        stack<pair<i64, int>> minima;
        stack<pair<i64, int>> best;

        dp[N] = -1e18;
        for (int i = N - 1; i >= 0; i--) {
            i64 best_val = old_dp[i + 1];
            while (!minima.empty() && A[minima.top().second] >= A[i]) {
                auto [val, idx] = minima.top(); minima.pop();
                
                if (!best.empty() && best.top().second == idx) best.pop();
                best_val = max(best_val, val);
            }

            minima.emplace(best_val, i);         
            if (best.empty() || best.top().first < best_val + A[i]) best.emplace(best_val + A[i], i);

            dp[i] = best.top().first;
        }

        swap(dp, old_dp);
    }

    cout << old_dp[0] << '\n';
}