#include <bits/stdc++.h>
using namespace std;

long long plan(int N, int M, int K, vector<int> A, vector<int> B, vector<int> L, vector<int> O, vector<int> T) {
    vector<vector<tuple<int, int, int, int, int>>> adj(N);

    for (int i = 0; i < M; i++) {
        adj[A[i]].emplace_back(B[i], L[i], O[i], adj[B[i]].size(), -1);
        adj[B[i]].emplace_back(A[i], L[i], O[i], adj[A[i]].size() - 1, -1);
    }

    vector<int> pos(K, -1);
    vector<vector<pair<int, int>>> true_adj(N);

    for (int i = 0; i < N; i++) {
        for (auto &[b, l, o, other, node_idx]: adj[i]) {
            if (pos[o] == -1) {
                pos[o] = true_adj.size();
                true_adj.emplace_back();

                true_adj[i].emplace_back(pos[o], T[o]);
                true_adj[pos[o]].emplace_back(i, 0);
            }
            node_idx = pos[o];
        }

        for (auto &[b, l, o, other, node_idx]: adj[i]) {
            pos[o] = -1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (auto &[b, l, o, other, node_idx]: adj[i]) {
            int other_node_idx = get<4>(adj[b][other]);
            true_adj[node_idx].emplace_back(other_node_idx, l);
        }
    }

    int true_n = true_adj.size();
    
    vector<long long> D(true_n, -1);
    
    vector<array<int, 3>> tree(true_n, {-1, -1, -1});
    queue<int> q;
    
    function<void(int)> reset = [&](int node) {
        if (node == -1) return;
        
        reset(tree[node][0]);
        reset(tree[node][2]);
        
        tree[node] = {-1, -1, -1};
        D[node] = -1;
    };
    
    D[0] = 0;
    q.push(0);
    
    while (!q.empty()) {
        int node = q.front(); q.pop();
        if (D[node] == -1) continue;

        for (auto [n, w]: true_adj[node]) {
            if (D[node] + w < D[n] || D[n] == -1) {
                if (D[n] != -1) {
                    if (tree[tree[n][1]][0] == n) {
                        tree[tree[n][1]][0] = tree[n][2];
                    } else {
                        tree[tree[n][1]][2] = tree[n][2];
                    }
                    
                    if (tree[n][2] != -1) {
                        tree[tree[n][2]][1] = tree[n][1];
                    }
                    reset(tree[n][0]);
                    tree[n] = {-1, -1, -1};
                }
                
                D[n] = D[node] + w;
                q.push(n);
                
                if (tree[node][0] != -1) tree[tree[node][0]][1] = n;
                tree[n][1] = node;
                tree[n][2] = tree[node][0];
                tree[node][0] = n;
            }
        }
    }

    return D[N - 1];
}