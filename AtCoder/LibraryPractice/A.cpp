#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> arr;
    
    int find(int node) {
        if (arr[node] < 0) return node;
        return arr[node] = find(arr[node]);
    }
    
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        
        if (arr[u] > arr[v]) swap(u, v);
        arr[u] += arr[v];
        arr[v] = u;
    }
    
    DSU(int size) : arr(size, -1) { }  
};

int main() {
    int N, Q; cin >> N >> Q;
    DSU dsu(N);
    
    while (Q--) {
        int t, u, v; cin >> t >> u >> v;
        if (t == 0) {
            dsu.merge(u, v);
        } else {
            cout << (dsu.find(u) == dsu.find(v)) << "\n";
        }
    }
}