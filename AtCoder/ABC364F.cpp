#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> next;

    int find(int node) {
        if (next[node] == -1) return node;
        return next[node] = find(next[node]);
    }

    void join(int u) {
        next[u] = find(u + 1);
    }

    DSU(int N) : next(N, -1) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, Q; cin >> N >> Q;

    vector<array<int, 3>> ranges(Q);
    for (auto &[c, l, r]: ranges) {
        cin >> l >> r >> c;
        l--, r--;
    }
    
    sort(ranges.begin(), ranges.end());

    DSU dsu(N);
    long long cost = 0;

    for (auto [c, l, r]: ranges) {
        cost += c;

        for (int i = dsu.find(l); i < r; i = dsu.find(i)) {            
            cost += c;
            dsu.join(i);
        }
    }

    if (dsu.find(0) == N - 1)
        cout << cost << '\n';
    else
        cout << "-1\n";
}