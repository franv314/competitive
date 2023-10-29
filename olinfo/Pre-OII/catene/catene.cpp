#include <bits/stdc++.h>
using namespace std;

#define MAXN 1'000'000

vector<pair<int, int>> adj[MAXN];

pair<long long, long long> dfs(int node, int par = -1) {
    long long sum = 0, best_diff_1 = 0, best_diff_2 = 0;

    for (auto [x, w]: adj[node]) {
        if (x == par) continue;
        auto [without, with] = dfs(x, node);

        sum += without;
        if (with + w - without > best_diff_1) {
            best_diff_2 = best_diff_1;
            best_diff_1 = with + w - without;
        } else if (with + w - without > best_diff_2) {
            best_diff_2 = with + w - without;
        }
    }

    return {sum + best_diff_1 + best_diff_2, sum + best_diff_1};
}

long long profitto_massimo(int N, int U[], int V[], int W[]){
    for (int i = 0; i < N - 1; i++) {
        adj[U[i] - 1].emplace_back(V[i] - 1, W[i]);
        adj[V[i] - 1].emplace_back(U[i] - 1, W[i]);
    }

    return dfs(0).first;
}