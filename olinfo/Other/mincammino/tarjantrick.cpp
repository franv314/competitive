#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

void mincammino(int N, int M, vector<int> X, vector<int> Y, vector<int> P, vector<int> &D) {
    vector<vector<pair<int, int>>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[X[i]].emplace_back(Y[i], P[i]);
    }
    
    fill(D.begin(), D.end(), -1);
    
    vector<array<int, 3>> tree(N, {-1, -1, -1});
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

        for (auto [n, w]: adj[node]) {
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
}