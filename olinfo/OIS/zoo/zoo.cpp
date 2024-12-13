#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> arr;
    int s;

    void add(int p, int d) {
        arr[p += s] += d;
        for (p >>= 1; p; p >>= 1)
            arr[p] += d;
    }

    int query(int l, int r) {
        int ans = 0;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += arr[l++];
            if (r & 1) ans += arr[--r];
        }
        return ans;
    }

    SegTree(int size) {
        s = 1 << (int)ceil(log2(size));
        arr.resize(2 * s);
    }
};

vector<int> bfs(int N, const vector<vector<int>> &adj, int source) {
    vector<int> dst(N, -1);
    queue<int> q;

    dst[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int x = q.front(); q.pop();
        
        for (auto y: adj[x]) {
            if (dst[y] == -1) {
                dst[y] = dst[x] + 1;
                q.push(y);
            }
        }
    }

    return dst;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> d0 = bfs(N, adj, 0);
    vector<int> dn = bfs(N, adj, N - 1);
    int d = dn[0];

    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int u, int v) {
        return d0[u] - dn[u] < d0[v] - dn[v];
    });

    SegTree ab(N), ba(N);
    for (int i: order)
        ab.add(dn[i], 1);
    
    long long ans = 0;
    for (int i: order) {
        ab.add(dn[i], -1);

        ans += ab.query(d - d0[i] - 1, N) + ba.query(d - dn[i] - 1, N);

        ba.add(d0[i], 1);
    }

    cout << ans / 2 - M << '\n';
}