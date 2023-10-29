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

    Fenwick(int size) : arr(size + 1) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> v(n);
    vector<vector<int>> adj(n);

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

    function<int(int, int)> dfs = [&](int node, int par) -> int {
        parent[node] = par;
        pair<int, int> max_size = {-1, -1};
        int size = 1;

        for (auto c: adj[node]) {
            if (c == par) continue;
            int c_size = dfs(c, node);
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

    dfs(0, -1);

    for (auto leaf: leaves) {
        for (int curr = leaf; curr != -1; curr = is_heavy[curr] ? parent[curr] : -1) {
            hld_pos[curr] = hld_order.size();
            hld_order.push_back(curr);

        }
        for (int curr = leaf; curr != -1; curr = is_heavy[curr] ? parent[curr] : -1) {
            hld_end[curr] = hld_order.size();
        }
    }

    Fenwick fenwick(n);
    for (int i = 0; i < n; i++) {
        fenwick.add(hld_pos[i], v[i]);
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int s, x; cin >> s >> x;
            s--;
            int diff = x - v[s];
            fenwick.add(hld_pos[s], diff);
            v[s] = x;
        } else {
            int s; cin >> s;
            long long ans = 0;
            for (s--; s != -1; s = parent[hld_order[hld_end[s] - 1]]) {
                ans += fenwick.query(hld_pos[s], hld_end[s]);
            }
            cout << ans << '\n';
        }
    }
}