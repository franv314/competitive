#include <bits/stdc++.h>
using namespace std;

bool visited[1000][1000][4];

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int N, M; cin >> N >> M;
    vector<tuple<short, short, short, bool>> adj[N][M][4];

    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            int poison; cin >> poison;
            if (!(poison & 1)) {
                adj[n][m][0].push_back({n, m, 1, 0});
                adj[n][m][1].push_back({n, m, 0, 0});
            }
            if (!(poison & 2)) {
                adj[n][m][1].push_back({n, m, 3, 0});
                adj[n][m][3].push_back({n, m, 1, 0});
            }
            if (!(poison & 4)) {
                adj[n][m][2].push_back({n, m, 3, 0});
                adj[n][m][3].push_back({n, m, 2, 0});
            }
            if (!(poison & 8)) {
                adj[n][m][0].push_back({n, m, 2, 0});
                adj[n][m][2].push_back({n, m, 0, 0});
            }

            if (n < N - 1) {
                adj[n][m][2].push_back({n + 1, m, 0, 1});
                adj[n][m][3].push_back({n + 1, m, 1, 1});
            }
            if (n > 0) {
                adj[n][m][0].push_back({n - 1, m, 2, 1});
                adj[n][m][1].push_back({n - 1, m, 3, 1});
            }
            if (m < M - 1) {
                adj[n][m][1].push_back({n, m + 1, 0, 1});
                adj[n][m][3].push_back({n, m + 1, 2, 1});
            }
            if (m > 0) {
                adj[n][m][0].push_back({n, m - 1, 1, 1});
                adj[n][m][2].push_back({n, m - 1, 3, 1});
            }
            if (n < N - 1 && m < M - 1)
                adj[n][m][3].push_back({n + 1, m + 1, 0, 1});
            if (n < N - 1 && m > 0)
                adj[n][m][2].push_back({n + 1, m - 1, 1, 1});
            if (n > 0 && m < M - 1)
                adj[n][m][1].push_back({n - 1, m + 1, 2, 1});
            if (n > 0 && m > 0)
                adj[n][m][0].push_back({n - 1, m - 1, 3, 1});
        }
    }
    
    deque<tuple<short, short, short, int>> q;
    q.push_back({0, 0, 0, 0});

    while (!q.empty()) {
        auto [n, m, p, d] = q.front();
        q.pop_front();
        if (visited[n][m][p]) continue;
        if (n == N - 1 && m == M - 1 && p == 3) {
            cout << d + 1 << endl;
            return 0;
        }

        visited[n][m][p] = true;
        for (auto [x, y, z, c]: adj[n][m][p]) {
            if (c == 0) q.push_front({x, y, z, d});
            else q.push_back({x, y, z, d + 1});
        }
    }
    cout << -1 << endl;
    return 0;
}