#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> arr;
    int s;

    void change(int x, int v) {
        x += s;
        arr[x] = v;
        for (x >>= 1; x > 0; x >>= 1)
            arr[x] = max(arr[2 * x], arr[2 * x + 1]);
    }

    int query(int l, int r) {
        int ma = 0;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ma = max(ma, arr[l++]);
            if (r & 1) ma = max(ma, arr[--r]);
        }
        return ma;
    }

    SegTree(int size) {
        s = 1 << (int)ceil(log2(size));
        arr.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> v(n);
    vector<vector<int>> adj(n);
    vector<vector<int>> bin_lift(n);

    for (auto &x: v) cin >> x;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parent(n, -1);
    vector<bool> is_heavy(n);
    vector<int> leaves;
    vector<int> hld_order = {-1};

    vector<int> hld_pos(n), hld_end(n);
    vector<int> depths(n);

    function<int(int, int, int)> dfs = [&](int node, int par, int d) -> int {
        depths[node] = d;
        parent[node] = par;

        int curr = par;
        for (int h = 0; curr != -1; h++) {
            bin_lift[node].push_back(curr);
            if (h < bin_lift[curr].size()) curr = bin_lift[curr][h];
            else curr = -1;
        }

        pair<int, int> max_size = {-1, -1};
        int size = 1;

        for (auto c: adj[node]) {
            if (c == par) continue;
            int c_size = dfs(c, node, d + 1);
            max_size = max(max_size, {c_size, c});
            size += c_size;
        }

        if (max_size.first == -1) {
            leaves.push_back(node);
        } else {
            is_heavy[max_size.second] = true;
        }

        return size;
    };

    auto lca = [&](int a, int b) {
        if (depths[a] > depths[b]) swap(a, b);

        for (int i = bin_lift[b].size(); i >= 0; i--) {
            if (i < bin_lift[b].size() && depths[bin_lift[b][i]] >= depths[a]) {
                b = bin_lift[b][i];
            }
        }

        if (a == b) return a;

        for (int i = bin_lift[a].size(); i >= 0; i--) {
            if (i < bin_lift[a].size() && bin_lift[a][i] != bin_lift[b][i]) {
                a = bin_lift[a][i];
                b = bin_lift[b][i];
            }
        }

        return parent[a];
    };

    dfs(0, -1, 0);

    for (auto leaf: leaves) {
        for (int curr = leaf; curr != -1; curr = is_heavy[curr] ? parent[curr] : -1) {
            hld_pos[curr] = hld_order.size();
            hld_order.push_back(curr);
        }
        for (int curr = leaf; curr != -1; curr = is_heavy[curr] ? parent[curr] : -1) {
            hld_end[curr] = hld_order.size();
        }
    }

    SegTree segtree(n);
    for (int i = 0; i < n; i++) {
        segtree.change(hld_pos[i], v[i]);
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int s, x; cin >> s >> x;
            s--;
            segtree.change(hld_pos[s], x);
        } else {
            int a, b; cin >> a >> b;
            a--, b--;
            int l = lca(a, b);
            int ans = 0;
            
            for (;;) {
                if (hld_end[a] != hld_end[l]) {
                    ans = max(ans, segtree.query(hld_pos[a], hld_end[a]));
                    a = parent[hld_order[hld_end[a] - 1]];
                } else {
                    ans = max(ans, segtree.query(hld_pos[a], hld_pos[l] + 1));
                    break;
                }
            }
            for (;;) {
                if (hld_end[b] != hld_end[l]) {
                    ans = max(ans, segtree.query(hld_pos[b], hld_end[b]));
                    b = parent[hld_order[hld_end[b] - 1]];
                } else {
                    ans = max(ans, segtree.query(hld_pos[b], hld_pos[l] + 1));
                    break;
                }
            }

            cout << ans << ' ';
        }
    }
}