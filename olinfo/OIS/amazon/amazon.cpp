#include <bits/stdc++.h>
using namespace std;

struct Info {
    int self_edges;
    vector<long long> edges;

    Info() : self_edges(0), edges() { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;

    map<long long, Info, greater<>> starts;
    
    for (int i = 0; i < N; i++) {
        long long L, R; cin >> L >> R;
    
        if (L == R) starts[L].self_edges++;
        else starts[L].edges.push_back(R);
    }

    map<long long, vector<long long>> dp;
    for (auto [l, info]: starts) {
        auto [self_edges, edges] = info;

        dp[l].assign(N + 1, -1);
        dp[l][0] = l;

        for (auto r: edges) {
            dp[l][1] = max(dp[l][1], r);
            if (starts.count(r)) {
                for (int i = 1; i <= N; i++) {
                    dp[l][i] = max(dp[l][i], dp[r][i - 1]);
                }
            }
        }

        vector<long long> old_dp = dp[l];

        for (int i = 1; i <= self_edges; i++) {
            for (int j = i; j <= N; j++) {
                dp[l][j] = max(dp[l][j], old_dp[j - i]);
            }
        }
    }

    int Q; cin >> Q;
    while (Q--) {
        long long X; cin >> X;
        int U, V; cin >> U >> V;

        if (!starts.count(X)) {
            if (U == 0) cout << X << ' ';
            else cout << -1 << ' ';
        } else {
            cout << *max_element(dp[X].begin() + U, dp[X].begin() + V + 1) << ' ';
        }
    }
}