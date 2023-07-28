#include <bits/stdc++.h>
using namespace std;

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    vector<vector<tuple<int, int, int>>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[A[i]].emplace_back(B[i], inizio[i], fine[i]);
        adj[B[i]].emplace_back(A[i], inizio[i], fine[i]);
    }
    
    vector<int> dst(N, 2e9);
    vector<bool> visited(N);
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > q;
    
    dst[0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [d, room] = q.top(); q.pop();
        if (room == N - 1) return d;
        if (visited[room]) continue;
        visited[room] = true;
        
        for (auto [neighbor, inizio, fine]: adj[room]) {
            if (fine > d) {
                int new_time = max(inizio, d) + 1;
                if (new_time < dst[neighbor]) {
                    q.emplace(dst[neighbor] = new_time, neighbor);
                }
            }
        }
    }
    
    return -1;
}