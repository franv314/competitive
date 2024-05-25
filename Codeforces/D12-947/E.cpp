#include <bits/stdc++.h>
using namespace std;
 
struct SegTree {
    vector<long long> sum;
    vector<pair<bool, long long>> lazy;
    int s;
 
    void update(int n, int nb, int ne) {
        if (lazy[n].first) {
            sum[n] = (long long)(ne - nb) * lazy[n].second;
            if (nb + 1 != ne) {
                lazy[2 * n] = lazy[2 * n + 1] = lazy[n];
            }
        } else {
            sum[n] += (long long)(ne - nb) * lazy[n].second;
            if (nb + 1 != ne) {
                lazy[2 * n].second += lazy[n].second;
                lazy[2 * n + 1].second += lazy[n].second;
            }
        }
        lazy[n] = {false, 0};
    }
 
    template<bool set>
    void change(int l, int r, int x, int n, int nb, int ne) {
        update(n, nb, ne);
        if (nb >= r || ne <= l) return;
        if (l <= nb && ne <= r) {
            if (set) lazy[n] = {true, x};
            else lazy[n].second += x;
 
            update(n, nb, ne);
            return;
        }
        change<set>(l, r, x, 2 * n, nb, (nb + ne) / 2);
        change<set>(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
        sum[n] = sum[2 * n] + sum[2 * n + 1];
    }
 
    long long query(int l, int r, int n, int nb, int ne) {
        update(n, nb, ne);
        if (nb >= r || ne <= l) return 0;
        if (l <= nb && ne <= r) return sum[n];
 
        return query(l, r, 2 * n, nb, (nb + ne) / 2)
             + query(l, r, 2 * n + 1, (nb + ne) / 2, ne);
    }
 
    template<bool set>
    void change(int l, int r, int x) { change<set>(l, r, x, 1, 0, s); }
    long long query(int l, int r) { return query(l, r, 1, 0, s); }
 
    SegTree(int size) {
        s = 1 << (int)ceil(log2(size));
        sum.resize(2 * s);
        lazy.resize(2 * s);
    }
};
 
void solve() {
    int n, q; cin >> n >> q;
    vector<int> v(n);
    vector<vector<int>> adj(n);
    vector<vector<int>> bin_lift(n);
    vector<int> depths(n);

    for (auto &x: v) cin >> x;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    int timer = 0;
    vector<int> parent(n), tin(n), tout(n);

    auto dfs = [&](auto &&dfs, int node, int par = -1, int d = 0) -> void {
        depths[node] = d;
        parent[node] = par;
        tin[node] = timer++;

        int curr = parent[node];
        for (int h = 0; curr != -1; h++) {
            bin_lift[node].push_back(curr);
            curr = bin_lift[curr].size() > h ? bin_lift[curr][h] : -1;
        }

        for (auto x: adj[node]) {
            if (x != par) {
                dfs(dfs, x, node, d + 1);
            }
        }

        tout[node] = timer;
    };

    auto lca = [&](int a, int b) {
        if (depths[a] > depths[b]) swap(a, b);
 
        for (int i = bin_lift[b].size() - 1; i >= 0; i--) {
            if (i < bin_lift[b].size() && depths[bin_lift[b][i]] >= depths[a]) {
                b = bin_lift[b][i];
            }
        }
 
        if (a == b) return a;
 
        for (int i = bin_lift[a].size() - 1; i >= 0; i--) {
            if (i < bin_lift[a].size() && bin_lift[a][i] != bin_lift[b][i]) {
                a = bin_lift[a][i];
                b = bin_lift[b][i];
            }
        }
 
        return parent[a];
    };

    dfs(dfs, 0);
    SegTree segtree(n);

    set<int> childless;
    vector<int> children(n);
    int black = 0;
    for (int i = 0; i < n; i++) {
        if (v[i]) {
            int node = i;
            segtree.change<false>(tin[node], tout[node], +1);
            black++;

            if (children[node] == 0) childless.insert(node);
            if (node != 0) {
                ++children[parent[node]];
                childless.erase(parent[node]);
            }
        }
    }

    auto count = [&](auto &&count, int curr, int tg, int c1, int c2, int par = -1) -> pair<int, int> {
        if (curr == tg) return {c1, c2};
        
        for (auto x: adj[curr]) {
            if (x != par) {
                auto ans = count(count, x, tg, c1 + 1, c2 + v[x], curr);
                if (ans.first != -1) return ans;
            }
        }

        return {-1, -1};
    };

    while (q--) {
        int node; cin >> node;
        node--;

        if (v[node]) {
            v[node] = 0;
            segtree.change<false>(tin[node], tout[node], -1);
            black--;

            childless.erase(node);
            if (node != 0) {
                if (--children[parent[node]] == 0 && v[parent[node]])
                    childless.insert(parent[node]);
            }
        } else {
            v[node] = 1;
            segtree.change<false>(tin[node], tout[node], +1);
            black++;

            if (children[node] == 0) childless.insert(node);
            if (node != 0) {
                ++children[parent[node]];
                childless.erase(parent[node]);
            }
        }

        if (black == 0) {
            cout << "No\n";
            continue;
        }

        assert(childless.size() != 0);
        if (childless.size() == 1) {
            cout << "Yes\n";
            continue;
        }

        int fst = *childless.begin();
        int lst = *childless.rbegin();
        int l = lca(fst, lst);

        int cnt = segtree.query(tin[fst], tin[fst] + 1)
                + segtree.query(tin[lst], tin[lst] + 1)
                - 2 * segtree.query(tin[l], tin[l] + 1)
                + v[l];
        int d = depths[fst] + depths[lst] - 2 * depths[l] + 1;

        if (cnt == black && cnt == d) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}