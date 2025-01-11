#include <bits/stdc++.h>
using namespace std;

long long comunica(int N, int M, int K, int S, int E, vector<int> A, vector<int> B, vector<int> T, vector<int> D) {
    vector<vector<array<int, 3>>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[A[i]].push_back({B[i], T[i], D[i]});
        adj[B[i]].push_back({A[i], T[i], D[i]});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;
    vector<long long> dst(N, 1e18);
    vector<bool> visited(N);

    q.emplace(dst[S] = 0, S);

    for (;;) {
        auto [len, node] = q.top(); q.pop();
        if (visited[node]) continue;
        if (node == E) return len;

        visited[node] = true;

        for (auto [neighbour, coso, sus]: adj[node]) {
            long long dist = (long long)K * coso - (long long)K * (K - 1) / 2 * sus;

            if (len + dist < dst[neighbour])
                q.emplace(dst[neighbour] = len + dist, neighbour);
        }
    }
}