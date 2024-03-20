#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M, K; cin >> N >> M >> K;
    vector<long long> A(N), B(M);
    for (auto &x: A) cin >> x;
    for (auto &x: B) cin >> x;

    vector<long long> p_a(N + 1), p_b(M + 1);
    for (int i = 0; i < N; i++) p_a[i + 1] = p_a[i] + A[i];
    for (int i = 0; i < M; i++) p_b[i + 1] = p_b[i] + B[i];

    if (p_a[N] != p_b[M]) {
        cout << "-1\n";
        return 0;
    }

    vector<long long> valid;
    for (int i = 0; i <= N; i++) {
        auto it = lower_bound(p_b.begin(), p_b.end(), p_a[i]);
        if (*it == p_a[i]) valid.push_back(*it);
    }

    vector<pair<int, long long>> dp(valid.size());
    vector<long long> cost(valid.size() + 1, -1e18);
    cost[0] = 1e18;

    for (int i = valid.size() - 1; i >= 0; i--) {
        int best = lower_bound(cost.begin(), cost.end(), valid[i], greater()) - cost.begin() - 1;

        dp[i] = {best + 1, cost[best]};
        cost[best + 1] = max(cost[best + 1], valid[i]);
    }

    {
        set<long long> lis;
        for (auto x: valid) {
            auto [it, ok] = lis.insert(x);
            if (ok && next(it) != lis.end()) lis.erase(next(it));
        }
        assert(lis.size() == dp[0].first);
    }

    if (dp[0].first <= K) {
        cout << "-1\n";
        return 0;
    }

    vector<int> s1, s2;
    int last = 0;
    for (int i = 1; i <= N; i++) {
        if (p_a[i] == dp[last].second) {
            s1.push_back(i);
            while (valid[last] != p_a[i]) last++;
        }
    }
    
    last = 0;
    for (int i = 1; i <= M; i++) {
        if (p_b[i] == dp[last].second) {
            s2.push_back(i);
            while (valid[last] != p_b[i]) last++;
        }
    }


    while (s1.size() >= K) s1.pop_back();
    while (s2.size() >= K) s2.pop_back();

    for (auto x: s1) cout << x << ' '; cout << '\n';
    for (auto x: s2) cout << x << ' '; cout << '\n';
}