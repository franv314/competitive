#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> arr;
    int cc;

    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        cc--;

        if (arr[u] > arr[v])
            swap(u, v);

        arr[u] += arr[v];
        arr[v] = u;
    }

    DSU(int size) : arr(size, -1), cc(size) { }
};

void solve() {
    int n, m1, m2; cin >> n >> m1 >> m2;
    vector<pair<int, int>> e1(m1), e2(m2);
    for (auto &[u, v]: e1) {
        cin >> u >> v;
        u--, v--;
    }    
    for (auto &[u, v]: e2) {
        cin >> u >> v;
        u--, v--;
    }

    DSU d1(n), d2(n);
    for (auto [u, v]: e2)
        d2.join(u, v);
    
    int cnt = 0;
    for (auto [u, v]: e1) {
        if (d2.find(u) == d2.find(v))
            d1.join(u, v);
        else
            cnt++;
    }

    cout << cnt + d1.cc - d2.cc << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
