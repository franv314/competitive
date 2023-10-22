#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000

bitset<MAXN> visited;
vector<pair<int, int>> adj[MAXN];

void dijkstra(int N, int S, vector<long long> &D) {
    visited.reset();
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;

    q.emplace(D[S] = 0, S);
    while (!q.empty()) {
        auto [d, n] = q.top(); q.pop();
        if (visited.test(n)) continue;
        visited.set(n);
        for (auto [x, w]: adj[n]) {
            if (d + w < D[x]) {
                q.emplace(D[x] = d + w, x);
            }
        }
    }
}

vector<long long> shorten(int N, int M, int Q, vector<long long> K, vector<int> A, vector<int> B, vector<int> C) {
    for (int i = 0; i < M; i++) {
        adj[A[i]].emplace_back(B[i], C[i]);
        adj[B[i]].emplace_back(A[i], C[i]);
    }

    vector<long long> D0(N, 1e18), D1(N, 1e18), D2(N, 1e18);
    dijkstra(N, 0, D0);
    dijkstra(N, 1, D1);
    dijkstra(N, 2, D2);

    long long one = 1e18;

    vector<pair<long long, long long>> two(N + 1);
    two[N] = {1e18, 1e18};

    for (int i = 0; i < N; i++) {
        two[i] = {2 * D1[i] + D0[i] + D2[i], D1[i]};
    }
    sort(two.begin(), two.end());

    vector<pair<long long, int>> NK(Q);
    vector<long long> ans(Q);

    for (int i = 0; i < Q; i++) NK[i] = {K[i], i};
    sort(NK.begin(), NK.end());

    int idx2 = 0;
    for (auto [pos, idx]: NK) {
        while (two[idx2].second < pos) {
            one = min(one, two[idx2].first - two[idx2].second);
            idx2++;
        }
        ans[idx] = min(two[idx2].first - 2 * pos, one - pos);
        if (ans[idx] <= 0) {
            ans[idx] = 0;
            break;
        }
    }

    return ans;
}