#include <bits/stdc++.h>
using namespace std;

int Analizza(int N, int M, int W, int L, int arco_da[], int arco_a[], int capacita[], int R, int C) {
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        adj[arco_da[i]].push_back({arco_a[i], capacita[i]});
        adj[arco_a[i]].push_back({arco_da[i], capacita[i]});
    }

    vector<bool> visited(N + 1);
    vector<int> flusso(N + 1, INT_MAX);
    vector<int> curr, next;

    flusso[W] = INT_MAX;
    curr.push_back(W);

    for (;;) {
        for (auto node: curr) {
            if (node == L) return flusso[node];
            visited[node] = true;
        }
        while (!curr.empty()) {
            int node = curr.back(); curr.pop_back();
            for (auto [neighbour, c]: adj[node]) {
                if (visited[neighbour]) continue;
                if (flusso[neighbour] == INT_MAX) next.push_back(neighbour);
                flusso[neighbour] = min(flusso[neighbour], min(flusso[node], c));
            }
        }
        swap(curr, next);
    }
}