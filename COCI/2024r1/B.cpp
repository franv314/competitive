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

    DSU(int size) : arr(size + 1, -1) {} 
};

int val(char c) {
    switch (c) {
    case 'C': return 1;
    case 'P': return 2;
    case 'N': return 4;
    case 'Z': return 8;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;

    vector<DSU> dsus(16, DSU(n * m));
    for (int i = 0; i < n; i++) {
        string row; cin >> row;
        for (int j = 0; j < m - 1; j++) {
            int v = val(row[j]);
            for (int d = 0; d < 16; d++) {
                if (d & v) {
                    dsus[d].join(m * i + j, m * i + j + 1);
                }
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        string row; cin >> row;
        for (int j = 0; j < m; j++) {
            int v = val(row[j]);
            for (int d = 0; d < 16; d++) {
                if (d & v) {
                    dsus[d].join(m * i + j, m * (i + 1) + j);
                }
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;

        int mi = 100;
        for (int d = 0; d < 16; d++) {
            if (dsus[d].find(x1 * m + y1) == dsus[d].find(x2 * m + y2)) {
                mi = min(mi, __builtin_popcount(d));
            }
        }

        cout << mi << '\n';
    }
}