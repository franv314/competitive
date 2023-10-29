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
    vector<int> l(n), r(n);
    int size = 1;

    for (auto &x: v) cin >> x;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    function<void(int, int)> dfs = [&](int node, int par) {
        l[node] = size++;
        for (auto c: adj[node]) {
            if (c == par) continue;
            dfs(c, node);
        }
        r[node] = size;
    };

    dfs(0, -1);

    Fenwick fenwick(n);
    for (int i = 0; i < n; i++) {
        fenwick.add(l[i], v[i]);
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int s, x; cin >> s >> x;
            s--;
            int diff = x - v[s];
            fenwick.add(l[s], diff);
            v[s] = x;
        } else {
            int s; cin >> s;
            s--;
            cout << fenwick.query(l[s], r[s]) << '\n';
        }
    }
}