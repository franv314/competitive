#include <bits/stdc++.h>
using namespace std;

void brucia(int N, vector<int> &M, vector<int> &B, vector<long long> &T) {
    vector<vector<pair<int, int>>> adj(N);

    vector<int> candles(N);
    iota(candles.begin(), candles.end(), 0);

    sort(candles.begin(), candles.end(), [&](int a, int b) {
        if (M[a] != M[b]) return M[a] < M[b];
        else return B[a] > B[b];
    });
    stack<int> burning;
    for (auto i: candles) {
        while (!burning.empty() && B[burning.top()] < M[i]) {
            burning.pop();
        }

        if (!burning.empty()) {
            adj[burning.top()].emplace_back(i, M[i] - M[burning.top()]);
            if (M[i] == M[burning.top()]) adj[i].emplace_back(burning.top(), 0);
        }

        if (B[i] < M[i]) continue;

        while (!burning.empty() && B[i] >= B[burning.top()]) {
            burning.pop();
        }
        burning.push(i);
    }

    while (!burning.empty()) burning.pop();
    reverse(candles.begin(), candles.end());

    for (auto i: candles) {
        while (!burning.empty() && B[burning.top()] > M[i]) {
            burning.pop();
        }

        if (!burning.empty()) {
            adj[burning.top()].emplace_back(i, M[burning.top()] - M[i]);
            if (M[i] == M[burning.top()]) adj[i].emplace_back(burning.top(), 0);
        }

        if (B[i] > M[i]) continue;

        while (!burning.empty() && B[i] <= B[burning.top()]) {
            burning.pop();
        }
        burning.push(i);
    }

    fill(T.begin(), T.end(), 1e18);
    vector<bool> visited(N);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;

    T[0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [t, n] = q.top(); q.pop();
        if (visited[n]) continue;
        visited[n] = true;

        for (auto [c, w]: adj[n]) {
            if (t + w < T[c]) {
                q.emplace(T[c] = t + w, c);
            }
        }
    }

    for (auto &t: T) {
        if (t == 1e18) {
            t = -1;
        }
    }
}
