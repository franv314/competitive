#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
    int N, M, X, Y;
    cin >> N >> M;
    cin >> X >> Y;

    vector<vector<pair<int, char>>> adj(N);

    for (int i = 0; i < M; i++) {
        int A, B;
        char L;
        cin >> A >> B >> L;
        adj[A].push_back({B, L});
        adj[B].push_back({A, L});
    }

    int risposta = INT_MAX;
    queue<tuple<int, int, int>> q;
    vector<vector<bool>> visited(N, vector<bool>(N));
    q.push({X, Y, 0});
    
    while (!q.empty()) {
        auto [x, y, d] = q.front(); q.pop();
        if (x == y) {
            risposta = min(risposta, 2 * d);
        }
        for (auto [n, c]: adj[x]) {
            if (n == y) {
                risposta = min(risposta, 2 * d + 1);
            }
        }
        if (visited[x][y]) continue;
        visited[x][y] = true;

        for (auto [nx, cx]: adj[x]) {
            for (auto [ny, cy]: adj[y]) {
                if (cx != cy || visited[nx][ny]) continue;
                q.push({nx, ny, d + 1});
            }
        }
    }

    if (risposta == INT_MAX) risposta = -1;

    out:
    cout << "Case #" << t << ": " << risposta << "\n";
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
