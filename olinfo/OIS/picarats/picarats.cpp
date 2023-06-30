#include <bits/stdc++.h>
using namespace std;

#define MAXN 10'001
#define MAXC 100

int N, M, C_0, P[MAXN];
vector<pair<int, int>> adj[MAXN];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> C_0;

    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    adj[N - 1].push_back({N, 0});

    vector<vector<int>> dst(N + 1, vector<int>(MAXC, 2e9));
    vector<vector<bool>> visited(N + 1, vector<bool>(MAXC, false));
    priority_queue<tuple<int, int, int>> q;

    q.push({0, 0, C_0});
    dst[0][C_0] = 0;
    while (!q.empty()) {
        auto [d, n, c] = q.top(); q.pop();
        if (visited[n][c]) continue;

        visited[n][c] = true;
        d *= -1;

        for (auto [dest, coins]: adj[n]) {
            for (int hints = 0; hints <= c; hints++) {
                int new_dst = max(d, P[n] >> hints);
                int new_coins = c - hints + coins;
                if (new_dst < dst[dest][new_coins]) {
                    dst[dest][new_coins] = new_dst;
                    q.push({-new_dst, dest, new_coins});
                }
            }
        }
    }
    cout << *min_element(dst[N].begin(), dst[N].end());
}