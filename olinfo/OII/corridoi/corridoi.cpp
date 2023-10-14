#include <bits/stdc++.h>
using namespace std;

void dijkstra(int N, int S, const vector<vector<pair<int, int>>> &adj, vector<long long> &D) {
    vector<bool> visited(N);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;

    q.emplace(D[S] = 0, S);
    while (!q.empty()) {
        auto [d, n] = q.top(); q.pop();
        if (visited[n]) continue;
        visited[n] = true;
        for (auto [x, w]: adj[n]) {
            if (d + w < D[x]) {
                q.emplace(D[x] = d + w, x);
            }
        }
    }
}

vector<long long> shorten(int N, int M, int Q, vector<long long> K, vector<int> A, vector<int> B, vector<int> C) {
    vector<vector<pair<int, int>>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[A[i]].emplace_back(B[i], C[i]);
        adj[B[i]].emplace_back(A[i], C[i]);
    }

    vector<long long> D0(N, 1e18), D1(N, 1e18), D2(N, 1e18);
    dijkstra(N, 0, adj, D0);
    dijkstra(N, 1, adj, D1);
    dijkstra(N, 2, adj, D2);

    multiset<long long> two, one;

    deque<array<long long, 3>> changes;

    long long mi = 1e18;
    for (int i = 0; i < N; i++) {
        long long common = D1[i];
        long long tot = 2 * common + D0[i] + D2[i];

        mi = min(mi, D0[i] + D1[i] + D2[i]);
        changes.push_back({common, tot, tot - common});
        two.insert(tot);
    }
    sort(changes.begin(), changes.end());

    vector<pair<long long, int>> NK(Q);
    vector<long long> ans(Q);

    for (int i = 0; i < Q; i++) NK[i] = {K[i], i};
    sort(NK.begin(), NK.end());

    for (auto [pos, idx]: NK) {
        if (pos >= mi) break;
        while (!changes.empty() && changes.front()[0] <= pos) {
            two.erase(two.find(changes.front()[1]));
            one.insert(changes.front()[2]);
            changes.pop_front();
        }
        ans[idx] = min(two.empty() ? LLONG_MAX : *two.begin() - 2 * pos, one.empty() ? LLONG_MAX : *one.begin() - pos);
    }

    return ans;
}
