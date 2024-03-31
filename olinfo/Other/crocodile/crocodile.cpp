#include <bits/stdc++.h>
using namespace std;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]){
    vector<vector<pair<int, int>>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[R[i][0]].emplace_back(R[i][1], L[i]);
        adj[R[i][1]].emplace_back(R[i][0], L[i]);
    }

    vector<int> visited(N);
    vector<long long> dst(N, 1e18);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;

    for (int i = 0; i < K; i++) {
        q.emplace(dst[P[i]] = 0, P[i]);
        visited[P[i]] = 1;
    }

    while (!q.empty()) {
        auto [d, node] = q.top(); q.pop();
        
        if (visited[node] == 0) {
            visited[node] = 1;
        } else if (visited[node] == 1) {
            dst[node] = d;
            visited[node] = 2;

            for (auto [x, w]: adj[node]) {
                q.emplace(d + w, x);
            }
        }
    }

    return dst[0];
}