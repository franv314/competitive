#include <bits/stdc++.h>
using namespace std;

int trova_sede(int N, int K, int A[], int B[], int P[], int filiali[]) {
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < N - 1; i++) {
        adj[A[i]].push_back({B[i], P[i]});
        adj[B[i]].push_back({A[i], P[i]});
    }

    vector<bool> ha_filiale(N + 1);
    vector<int> filiali_sottoalbero(N + 1);
    for (int i = 0; i < K; i++) {
        ha_filiale[filiali[i]] = true;
        filiali_sottoalbero[filiali[i]]++;
    }
    
    function<void(int, int)> dfs1 = [&](int node, int parent) {
        for (auto [n, w]: adj[node]) {
            if (n == parent) continue;
            dfs1(n, node);
            filiali_sottoalbero[node] += filiali_sottoalbero[n];
        }
    };

    long long dist = 0;
    pair<long long, int> ans = {LLONG_MAX, -1};
    function<void(int, int, int)> dfs2 = [&](int node, int parent, long long depth) {
        if (ha_filiale[node]) dist += depth;
        for (auto [n, w]: adj[node]) {
            if (n == parent) continue;
            dfs2(n, node, depth + w);
        }
    };

    function<void(int, int)> dfs3 = [&](int node, int parent) {
        ans = min(ans, {dist, node});
        for (auto [n, w]: adj[node]) {
            if (n == parent) continue;
            
            int avv = filiali_sottoalbero[n];
            int all = K - avv;
            dist += (long long)(all - avv) * w;
            dfs3(n, node);
            dist -= (long long)(all - avv) * w;
        }
    };

    dfs1(1, 0);
    dfs2(1, 0, 0);
    dfs3(1, 0);
    return ans.second;
}