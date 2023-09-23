#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> arr;

    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (arr[u] > arr[v]) swap(u, v);
        arr[u] += arr[v];
        arr[v] = u;
    }

    DSU(int size) : arr(size, -1) { }
};

int progetta(int N, int M, int K, vector<int> &A, vector<int> &B, vector<int> &W) {
    vector<tuple<int, int, int>> edges(M);
    for (int i = 0; i < M; i++) {
        edges[i] = {W[i], A[i] - 1, B[i] - 1};
    }

    sort(edges.rbegin(), edges.rend());
    DSU dsu(N);

    int cc = N;
    long long ans = 0;
    for (auto [w, a, b]: edges) {
        if (cc == K || dsu.find(a) == dsu.find(b)) continue;
        ans += w;
        dsu.join(a, b);
        cc--;
    }
    return ans;
}