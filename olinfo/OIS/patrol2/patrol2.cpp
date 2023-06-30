#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, L; cin >> N >> M >> L;

    set<int> adj[N];
    for (int i = 0; i < M; ++i) {
        int A, B; cin >> A >> B;
        adj[A].insert(B);
        adj[B].insert(A);
    }

    vector<int> C(L);
    for (auto &x : C) cin >> x;

    priority_queue<pair<int, int>> q;
    q.push({0, 0});
    vector<bool> visited(N);

    while (!q.empty()) {
        auto [dst, node] = q.top(); q.pop();
        if (visited[node]) continue;

        dst *= -1;
        if (node == N - 1) {
            cout << dst << endl;
            return 0;
        }

        visited[node] = true;

        for (auto n: adj[node]) {
            if (!visited[n]) {
                if (C[(dst + 1) % L] != n) {
                    q.push({- dst - 1, n});
                } else {
                    q.push({- dst - 2, n});
                }
            }
        }
    }

    cout << -1 << endl;  // print the result
    return 0;
}