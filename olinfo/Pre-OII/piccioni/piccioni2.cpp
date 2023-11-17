#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Node {
    vector<pair<int, int>> adj;
    int dfs_l, dfs_r;
    int depth;
};

vector<vector<Node>> nodes;
vector<int> curr_ver;
vector<pair<int, int>> dfs_order;

struct Info {
    int cnt;
    i64 depths;

    void operator+=(const Info &o) {
        cnt += o.cnt;
        depths += o.depths;
    }

    Info(int cnt, i64 depths) : cnt(cnt), depths(depths) { }
    Info() : Info(0, 0) { }
};

Info operator+(const Info &a, const Info &b) {
    return {a.cnt + b.cnt, a.depths + b.depths};
}

struct Fenwick {
    vector<Info> arr;

    void add(int x, Info info) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += info;
    }

    Info query(int x) {
        Info ans;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    Fenwick() { }
    Fenwick(int size) : arr(size + 1) { }
};

struct SegTree {
    struct SegmentNode {
        vector<int> depths;
        Fenwick fenwick;

        void insert(int d, Info info) {
            int x = upper_bound(depths.begin(), depths.end(), d) - depths.begin();
            fenwick.add(x, info);
        }

        Info sum_until(int d) {
            int x = upper_bound(depths.begin(), depths.end(), d) - depths.begin();
            return fenwick.query(x);
        }

        SegmentNode() {}
        SegmentNode(int d) : depths(), fenwick(1) {
            depths.push_back(d);
        }
        SegmentNode(const SegmentNode &a, const SegmentNode &b) {
            depths.resize(a.depths.size() + b.depths.size());
            merge(a.depths.begin(), a.depths.end(), b.depths.begin(), b.depths.end(), depths.begin());
            depths.resize(unique(depths.begin(), depths.end()) - depths.begin());

            fenwick = Fenwick(depths.size());
        }
    };

    vector<SegmentNode> arr;
    vector<bool> exists;
    int s;

    void flip(int pos) {
        int p = pos;
        auto [n, v] = dfs_order[pos];
        int d = nodes[n][v].depth;

        for (pos += s; pos; pos >>= 1) {
            if (exists[p]) {
                arr[pos].insert(d, {-1, -d});
            } else {
                arr[pos].insert(d, {1, d});
            }
        }

        exists[p] = !exists[p];
    }

    Info query(int l, int r, int max_d) {
        Info ans = {0, 0};
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += arr[l++].sum_until(max_d);
            if (r & 1) ans += arr[--r].sum_until(max_d);
        }
        return ans;
    }

    SegTree(const vector<pair<int, int>> &A) {
        s = 1 << (int)ceil(log2(A.size()));
        arr.resize(2 * s);
        exists.assign(A.size(), false);

        for (int i = 0; i < A.size(); i++) arr[i + s] = SegmentNode(nodes[A[i].first][A[i].second].depth);
        for (int i = s - 1; i; i--) arr[i] = SegmentNode(arr[2 * i], arr[2 * i + 1]);
    }
};

void dfs(int node, int val, int d = 0) {
    nodes[node][val].depth = d;
    nodes[node][val].dfs_l = dfs_order.size();

    dfs_order.emplace_back(node, val);

    for (auto [n, v]: nodes[node][val].adj)
        dfs(n, v, d + 1);

    nodes[node][val].dfs_r = dfs_order.size();
}

void calcola_disagio(int N, int Q, int P[], int K[], int u[], int v[], i64 risposta[]) {
    nodes.assign(N + 1, vector<Node>(1));
    curr_ver.assign(N + 1, 0);
    for (int i = 2; i <= N; i++)
        nodes[P[i]][0].adj.emplace_back(i, 0);

    for (int i = 0; i < Q; i++) {
        if (v[i] != -1) {
            nodes[v[i]].back().adj.emplace_back(u[i], nodes[u[i]].size());
            nodes[u[i]].emplace_back();
        }
    }

    dfs(1, 0);
    SegTree segtree(dfs_order);
    for (int i = 1; i <= N; i++) {
        segtree.flip(nodes[i][0].dfs_l);
    }

    for (int i = 0; i < Q; i++) {
        int &cv = curr_ver[u[i]];
        if (v[i] != -1) {
            segtree.flip(nodes[u[i]][cv].dfs_l);
            segtree.flip(nodes[u[i]][++cv].dfs_l);
        } else {
            auto [cnt, depths] = segtree.query(
                nodes[u[i]][cv].dfs_l + 1,
                nodes[u[i]][cv].dfs_r,
                min(nodes[u[i]][cv].depth + K[u[i]], (int)dfs_order.size())
            );
            *(risposta++) = (i64)cnt * (K[u[i]] + 1 + nodes[u[i]][cv].depth) - depths;
        }
    }
}