#include <bits/stdc++.h>
using namespace std;

struct DSU {
    map<int, int> arr;

    void create_node(int val) {
        if (!arr.count(val)) arr[val] = -1;
    }

    int find(int node) {
        create_node(node);
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        arr[u] = v;
    };
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    DSU dsu;
    set<int, greater<>> vals;
    
    for (int i = 0; i < n; i++) {
        int first = dsu.find(a[i] + i + 1);
        
        if (first <= a[i]) continue;

        vals.insert(first);
        dsu.join(first, first - 1);
    }

    for (auto x: vals) cout << x << ' '; cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}