#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> arr;

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
    } 

    DSU(int size) : arr(size, -1) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DSU dsu(N);

    vector<int> max_r(N, -1);
    for (int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].push_back(N);
        
        int l = 0;
        for (auto j: adj[i]) {
            max_r[l] = max(max_r[l], j);
            if (j != l) dsu.join(i, l);
            l = j + 1;
        }
    }

    int r = 0;
    for (int i = 0; i < N; i++) {
        if (r > i) dsu.join(i, i - 1);
        r = max(r, max_r[i]);
    }

    vector<vector<int>> by_repr(N);
    for (int i = 0; i < N; i++)
        by_repr[dsu.find(i)].push_back(i);

    cout << count_if(by_repr.begin(), by_repr.end(), [](const vector<int> &cc) { return !cc.empty(); }) << '\n';
    for (auto &cc: by_repr) {
        if (cc.empty()) continue;
        cout << cc.size() << ' ';
        for (auto x: cc) cout << x << ' ';
        cout << '\n';
    }
}