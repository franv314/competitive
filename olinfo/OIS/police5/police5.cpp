#include <bits/stdc++.h>
using namespace std;

#define MAXN 10'000

// input data
int N, M, T;

vector<tuple<int, int, bool>> adj[MAXN];

int main() {
    cin >> N >> M >> T;

    for (int i=0; i<M; i++) {
        int A, B, C;
        bool E;
        cin >> A >> B >> C >> E;
        adj[A].push_back({B, C, E});
    }

    vector<long long> dst(N, 1e18);
    vector<bool> visited(N, false);
    priority_queue<tuple<int, int>> q;
    q.push({0, 0});
    dst[0] = 0;
    while (!q.empty()) {
        auto [d, node] = q.top();
        d *= -1;
        q.pop();
        if (visited[node]) continue;
        if (node == N - 1) {
            cout << d << endl;
            return 0;
        }

        visited[node] = true;

        for (auto [N, D, E]: adj[node]) {
            if ((!E || d + D <= T) && d + D < dst[N]) {
                dst[N] = d + D;
                q.push({-dst[N], N});
            }
        }
    }
    cout << -1 << endl;
    return 0;
}