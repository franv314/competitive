#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<long long> arr;

    void add(int x, int d) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += d;
    }

    long long query(int x) {
        long long ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    long long query(int l, int r) {
        return query(r - 1) - query(l - 1);
    }

    Fenwick(int size) : arr(size + 1) {}
};

void solve() {
    int q; cin >> q;

    vector<vector<pair<int, int>>> adj(1), add(1);

    for (int i = 1; i <= q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int v; cin >> v;
            adj[v - 1].emplace_back(adj.size(), i);
            adj.emplace_back();
            add.emplace_back();
        } else {
            int v, x; cin >> v >> x;
            add[v - 1].emplace_back(x, i);
        }
    }

    Fenwick fenwick(q);
    vector<long long> ans(adj.size());
    
    function<void(int, int)> dfs = [&](int node, int time) {
        for (auto [x, t]: add[node]) {
            fenwick.add(t, x);
        }

        ans[node] = fenwick.query(time, q + 1);

        for (auto [c, t]: adj[node]) {
            dfs(c, t);
        }

        for (auto [x, t]: add[node]) {
            fenwick.add(t, -x);
        }
    };

    dfs(0, 1);

    for (auto x: ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
}