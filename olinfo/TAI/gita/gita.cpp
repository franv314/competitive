#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define MAXN 1000000
#define LSB(x) (x & -x)

class Fenwick {
    vector<int> tree;
    int size;

public:

    void print() {
        for (int i = 1; i <= size; i++) cout << tree[i] << " ";
        cout << endl;
    }

    int lower_bound(int m) {
        int p = 0;
        for (int d = 1 << (int)log2(size); d; d >>= 1) {
            if (tree[p + d] < m) {
                m -= tree[p + d];
                p += d;
            }
        }
        return p + 1;
    }

    void add(int x, int d) {
        for (; x <= size; x += LSB(x)) {
            tree[x] += d;
        }
    }

    Fenwick () { }
    Fenwick(int N) {
        size = N;
        tree = vector<int>(N + 1, 0);
    }
};

Fenwick find_nth;
vector<pair<int, int>> d;
vector<int> val;
vector<int> D;
vector<int> C;
vector<int> adj[MAXN];
vector<int> naive;

int dfs(int node, int depth_parity, int parent) {
    find_nth.add(D[node], 1);

    int ret = depth_parity * (-1e9);
    for (auto child: adj[node]) {
        if (child != parent) {
            int c = dfs(child, depth_parity * -1, node);
            ret = depth_parity * max(depth_parity * ret, depth_parity * c);
        }
    }

    if (ret == depth_parity * (-1e9)) {
        ret = find_nth.lower_bound(C[node] + 1);
    }

    find_nth.add(D[node], -1);
    
    return ret;
}

int dfs_naive(int node, int depth_parity, int parent) {
    naive.push_back(D[node]);

    int ret = depth_parity * (-1e9);
    for (auto child: adj[node]) {
        if (child != parent) {
            int c = dfs_naive(child, depth_parity * -1, node);
            ret = depth_parity * max(depth_parity * ret, depth_parity * c);
        }
    }

    if (ret == depth_parity * (-1e9)) {
        nth_element(naive.begin(), naive.begin() + C[node], naive.end());
        ret = naive[C[node]];
    }

    if (naive.size()) naive.pop_back();

    return ret;
}


int visita(int N, vector<int> &A, vector<int> &B, vector<int> &dolcezza, vector<int> &C) {
    find_nth = Fenwick(N);
    ::C = C;
    d.reserve(N);
    val.resize(N + 1);
    D.resize(N);
    for (int i = 0; i < N - 1; i++) {
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }
    
    if (N < 100) {
        D = dolcezza;
        return dfs_naive(0, 1, -1);
    }
    
    for (int i = 0; i < N; i++) d.push_back({dolcezza[i], i});
    sort(d.begin(), d.end());

    int curr = 0, old = 0;
    for (auto x: d) {
        curr += (old != x.first);
        old = x.first;
        D[x.second] = curr;
        val[curr] = dolcezza[x.second];
    }

    return val[dfs(0, 1, -1)];
}