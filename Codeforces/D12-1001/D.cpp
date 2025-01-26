#include <bits/stdc++.h>
using namespace std;

#define int long long

struct SegTree {
    vector<int> arr;
    int s;

    int query(int l, int r) {
        int ans = 0;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = max(ans, arr[l++]);
            if (r & 1) ans = max(ans, arr[--r]);
        }

        return ans;
    }

    SegTree(const vector<int> &a) {
        s = 1 << (int)ceil(log2(a.size()));
        arr.resize(2 * s);

        for (int i = 0; i < a.size(); i++)
            arr[i + s] = a[i];
        for (int i = s - 1; i; i--)
            arr[i] = max(arr[2 * i], arr[2 * i + 1]);
    }
};

void solve() {
    int n; cin >> n;

    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++)
        cin >> l[i] >> r[i];

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    if (n <= 2) {
        cout << *max_element(l.begin(), l.end()) << '\n';
        return;
    }

    int timer = 0;
    vector<int> final(n), tin(n), tout(n);
    vector<int> pay(n), paysum(n);

    auto dfs = [&](auto &&dfs, int node, int par = -1) -> int {
        tin[node] = timer++;

        int s = 0, m = -1e9;
        for (auto ch: adj[node]) {
            if (ch == par)
                continue;
            int d = dfs(dfs, ch, node);

            paysum[node] += paysum[ch];

            if (d > r[node]) s += d - r[node];
            m = max(m, d);
        }

        tout[node] = timer;

        if (m > r[node]) {
            pay[node] = s;
        } else {
            pay[node] = 0;
        }
        paysum[node] += pay[node];

        return final[tin[node]] = clamp(m, l[node], r[node]);
    };

    int root;
    for (int i = 0; i < n; i++)
        if (adj[i].size() > 1)
            root = i;

    dfs(dfs, root);

    SegTree segtree(final);
    int ans = 0;

    for (int i = 0; i < n; i++) {

        int ma1 = segtree.query(0, tin[i] + 1) + paysum[i];
        int ma2 = segtree.query(tout[i], n) + paysum[i];

        ans = max({ans, ma1, ma2});
    }

    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
