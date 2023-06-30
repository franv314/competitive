#include <bits/stdc++.h>
using namespace std;

#define MAXW 5'000'001

class DSU {
    vector<int> next;

public:

    int find_next(int node) {
        if (next[node] == -1) return node;
        return next[node] = find_next(next[node]);
    }

    void skip(int node) {
        next[node] = node + 1;
    }

    DSU(int size) : next(size + 1, -1) { }
};

class PhiTree {
    int W;
    vector<int> phi, depth;

    void sieve() {
        iota(phi.begin(), phi.end(), 0);

        for (int i = 2; i < W; i++) {
            if (phi[i] == i) {
                for (int j = i; j < W; j += i) {
                    phi[j] -= phi[j] / i;
                }
            }
            depth[i] = depth[phi[i]] + 1;
        }
    }

public:

    int get_phi(int x) { return phi[x]; }

    tuple<int, int, int> lca(int a, int b) {
        int cost_a = 0, cost_b = 0;
        if (depth[a] > depth[b]) {
            while (depth[a] != depth[b]) {
                a = phi[a];
                cost_a++;
            }
        } else {
            while (depth[b] != depth[a]) {
                b = phi[b];
                cost_b++;
            }
        }
        while (a != b) {
            a = phi[a], b = phi[b];
            cost_a++, cost_b++;
        }
        return {a, cost_a, cost_b};
    }

    PhiTree(int W) : W(W), phi(W), depth(W) { sieve(); }
};

class SegTree {
    typedef tuple<int, int, long long> node_t;

    int size;
    DSU dsu;
    PhiTree phi;
    vector<node_t> arr;

    node_t merge(node_t l, node_t r) {
        if (l == (node_t){0, 0, 0}) return r;
        if (r == (node_t){0, 0, 0}) return l;

        auto [size_l, val_l, cost_l] = l;
        auto [size_r, val_r, cost_r] = r;

        auto [val, cost_a, cost_b] = phi.lca(val_l, val_r);
        return {size_l + size_r, val, cost_l + cost_r + size_l * (long long)cost_a + size_r * (long long)cost_b};
    }

    void update(int x) {
        x += size;
        get<1>(arr[x]) = phi.get_phi(get<1>(arr[x]));
        for (x >>= 1; x; x >>= 1)
            arr[x] = merge(arr[2 * x], arr[2 * x + 1]);
    }

public:

    void update(int l, int r) {
        for (int i = dsu.find_next(l); i < r; i = dsu.find_next(i + 1)) {
            update(i);
            if (get<1>(arr[i + size]) == 1) dsu.skip(i);
        }
    }

    node_t query(int l, int r) {
        node_t ans = {0, 0, 0};
        for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = merge(ans, arr[l++]);
            if (r & 1) ans = merge(ans, arr[--r]);
        }
        return ans;
    }

    SegTree(vector<int> val) : phi(MAXW), dsu(val.size()) {
        size = 1 << (int)ceil(log2(val.size()));
        arr.resize(2 * size, {0, 0, 0});

        for (int i = 0; i < val.size(); i++)
            arr[i + size] = {1, val[i], 0};
        
        for (int i = size - 1; i; i--)
            arr[i] = merge(arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    SegTree segtree(a);
    while (m--) {
        int t, l, r; cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            segtree.update(l, r + 1);
        } else {
            cout << get<2>(segtree.query(l, r + 1)) << "\n";
        }
    }
}