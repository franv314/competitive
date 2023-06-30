#include <bits/stdc++.h>
using namespace std;

#define MAXN 2'000

int N;
vector<pair<int, int>> adj[MAXN];

int dijkstra(int start) {
    vector<int> dst(N, 1e9);
    vector<bool> visited(N, false);
    priority_queue<pair<int, int>> q;

    dst[start] = 0;
    q.push({0, start});
    while (!q.empty()) {
        auto [d, node] = q.top(); q.pop();
        if (visited[node]) continue;

        visited[node] = true;
        d *= -1;
        for (auto [n, w]: adj[node]) {
            if (d + w < dst[n]) {
                dst[n] = d + w;
                q.push({-dst[n], n});
            }
        }
    }
    return *max_element(dst.begin(), dst.end());
}

int latenza(int N, int M, int A[], int B[], int L[]) {
    ::N = N;
    for (int i = 0; i < M; i++) {
        adj[A[i] - 1].push_back({B[i] - 1, L[i]});
        adj[B[i] - 1].push_back({A[i] - 1, L[i]});
    }

    int ans = INT_MIN;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dijkstra(i));
    }
    return ans;
}