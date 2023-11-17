#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int R, C, N; cin >> R >> C >> N;

    unordered_map<int, vector<pair<long long, int>>> rows, cols, diag1, diag2;

    for (int i = 0; i < N; i++) {
        int r, c; cin >> r >> c;

        long long val = 2LL * r + c;
        rows[r].emplace_back(val, i);
        cols[c].emplace_back(val, i);
        diag1[r + c].emplace_back(val, i);
        diag2[r - c].emplace_back(val, i);
    }

    vector<vector<int>> adj(N);
    int cnt = 0;

    for (auto &y: {rows, cols, diag1, diag2}) {
        for (auto &[_, z]: y) {
            auto x = z;
            sort(x.begin(), x.end());
            for (int i = 0; i < x.size() - 1; i++) {
                cnt++;
                auto [v1, i1] = x[i];
                auto [v2, i2] = x[i + 1];
                adj[i1].push_back(i2);
                adj[i2].push_back(i1);
            }
        }
    }

    assert(cnt <= 4 * N);

    vector<bool> visited(N);
    int cc = 0;
    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;
        cc++;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            if (visited[x]) continue;
            visited[x] = true;
            for (auto y: adj[x]) {
                if (!visited[y]) {
                    q.push(y);
                }
            }
        }
    }

    long long ans = 1;
    for (int i = 0; i < cc; i++) ans = ans * 2 % MOD;

    cout << ans << '\n';
}