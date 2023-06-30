#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

typedef tuple<long long, bool, int> node_info;

vector<tuple<int, int, bool>> adj[MAXN];

long long fuggi(int N, int M, vector<int> A, vector<int> B, vector<int> T, vector<int> R) {
    for (int i = 0; i < M; i++)
        adj[B[i]].push_back({A[i], T[i], R[i]});
    
    vector<long long> dst(N, 1e18);
    vector<int> visited(N, 0);
    
    priority_queue<node_info, vector<node_info>, greater<node_info>> q;
    q.push({0, false, N - 1});
    dst[N - 1] = 0;
    while (!q.empty()) {
        auto [dist, red, node] = q.top(); q.pop();
        if (visited[node] == 2) continue;

        if (red) {
            visited[node] = 1;
        } else {
            dst[node] = dist - visited[node];
            for (auto [n, w, r]: adj[node]) {
                q.push({dst[node] + w, r, n});
            }
            visited[node] = 2;
        }
    }

    return dst[0];
}