#include <bits/stdc++.h>
using namespace std;

long long costruisci(int N, int M, vector<long long>& H, vector<int>& A, vector<int>& B, vector<int>& C) {
    vector<vector<pair<int, int>>> adj(N);
    for (int i = 0; i < M; i++) adj[A[i]].emplace_back(B[i], C[i]);
    
    vector<bool> visited(N);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;
    for (int i = 0; i < N; i++) q.emplace(H[i], i);

    while (!q.empty()) {
        auto [d, n] = q.top(); q.pop();
        if (visited[n]) continue;
        visited[n] = true;

        for (auto [x, w]: adj[n]) {
            if (d + w < H[x]) {
                q.emplace(H[x] = d + w, x);
            }
        }
    }
    return accumulate(H.begin(), H.end(), 0LL);
}
