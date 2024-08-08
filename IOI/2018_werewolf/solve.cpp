#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;

template<typename Cmp>
class Tree {
    vector<vector<int>> adj;
    vector<int> time;
    Cmp cmp;

    int t;
    vector<vector<int>> bin_lift;
    vector<pair<int, int>> timer;
    vector<int> pos_of;

    void dfs(int node, int par = -1) {
        if (par != -1) {
            bin_lift[node].push_back(par);
            for (int i = 0; bin_lift[bin_lift[node][i]].size() > i; i++) {
                bin_lift[node].push_back(bin_lift[bin_lift[node][i]][i]);
            }
        }

        timer[node].first = t;
        if (adj[node].empty())
            pos_of[node] = t++;

        for (auto x: adj[node])
            dfs(x, node);
    
        timer[node].second = t;
    }

public:

    pair<int, int> get_range(int node, int limit) {
        for (int i = bin_lift[node].size() - 1; i >= 0; i--)
            if (bin_lift[node].size() > i && cmp(time[bin_lift[node][i]], limit))
                node = bin_lift[node][i];
        return timer[node];
    }

    int get_pos(int node) { return pos_of[node]; }

    Tree(int N, const vector<vector<int>> &adj, const vector<int> &time) 
        : adj(adj), time(time), cmp(), bin_lift(adj.size()), t(0), timer(adj.size()), pos_of(N)
    { dfs(adj.size() - 1); }
};

class DSU {
    vector<int> arr;
    vector<int> root;
    vector<int> time;
    vector<vector<int>> adj;

public:

    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }

    void join(int u, int v, int t) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (arr[v] < arr[u]) swap(u, v);
        arr[u] += arr[v];
        arr[v] = u;

        adj.push_back({root[u], root[v]});
        time.push_back(t);
        root[u] = adj.size() - 1;
    }

    template<typename Cmp>
    Tree<Cmp> get_tree() { return Tree<Cmp>(arr.size(), adj, time); }

    DSU(int N, int start_t) : arr(N, -1), root(N), time(N, start_t), adj(N) {
        time.reserve(2 * N - 1);
        adj.reserve(2 * N - 1);
        iota(root.begin(), root.end(), 0);
    }
};

class SegTree {
    vector<int> arr;
    int s;

public:

    void add(int pos, int d) {
        pos += s;
        arr[pos] += d;
        
        for (pos >>= 1; pos; pos >>= 1)
            arr[pos] = arr[2 * pos] + arr[2 * pos + 1];
    }

    int query(int l, int r) {
        int ans = 0;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += arr[l++];
            if (r & 1) ans += arr[--r];
        }
        return ans;
    }

    SegTree(int N) {
        s = 1 << (int)ceil(log2(N));
        arr.resize(2 * s);
    }
};

vector<int> check_validity(
    int N,
    vector<int> X, vector<int> Y,
    vector<int> S, vector<int> E,
    vector<int> L, vector<int> R
) {
    int M = X.size();
    int Q = S.size();

    vector<vector<int>> adj_wolf(N), adj_human(N);
    for (int i = 0; i < M; i++) {
        auto [u, v] = minmax(X[i], Y[i]);
        adj_human[u].push_back(v);
        adj_wolf[v].push_back(u);
    }

    DSU human_dsu(N, N);
    for (int i = N - 1; i >= 0; i--)
        for (auto j: adj_human[i])
            human_dsu.join(i, j, i);
    Tree human_tree = human_dsu.get_tree<greater_equal<int>>();

    DSU wolf_dsu(N, -1);
    for (int i = 0; i < N; i++)
        for (auto j: adj_wolf[i])
            wolf_dsu.join(i, j, i);
    Tree wolf_tree = wolf_dsu.get_tree<less_equal<int>>();

    vector<int> on(N + 1);
    vector<vector<array<int, 4>>> queries(N + 1);
    for (int i = 0; i < N; i++)
        on[human_tree.get_pos(i)] = wolf_tree.get_pos(i);

    for (int i = 0; i < Q; i++) {
        auto [l1, r1] = human_tree.get_range(S[i], L[i]);
        auto [l2, r2] = wolf_tree.get_range(E[i], R[i]);

        queries[l1].push_back({l2, r2, i, -1});
        queries[r1].push_back({l2, r2, i, +1});
    }

    vector<int> ans(Q);
    SegTree segtree(N);    

    for (int i = 0; i <= N; i++) {
        for (auto [l, r, idx, mult]: queries[i])
            ans[idx] += mult * segtree.query(l, r);
        segtree.add(on[i], +1);
    }

    for (int i = 0; i < Q; i++)
        ans[i] = ans[i] > 0;

    return ans;
}
