#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> arr;
    int ma, cc;

    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (arr[u] > arr[v]) swap(u, v);

        arr[u] += arr[v];
        arr[v] = u;

        ma = max(ma, -arr[u]);
        cc--;
    }

    DSU(int N) : arr(N, -1), ma(1), cc(N) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    
    DSU dsu(n);
    while (m--) {
        int u, v; cin >> u >> v;
        dsu.join(u - 1, v - 1);
        cout << dsu.cc << " " << dsu.ma << "\n";
    }
}