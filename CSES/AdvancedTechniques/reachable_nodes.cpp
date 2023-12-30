#pragma GCC target("popcnt")
#include <bits/stdc++.h>
using namespace std;

#define MAXN 50'000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
    }

    vector<optional<bitset<MAXN>>> reach(n);
    function<void(int)> get_reach = [&](int node) {
        reach[node] = bitset<MAXN>();
        reach[node].value().set(node);
        for (auto n: adj[node]) {
            if (!reach[n]) get_reach(n);
            reach[node].value() |= reach[n].value();
        }
    };

    for (int i = 0; i < n; i++) {
        get_reach(i);
        cout << reach[i].value().count() << ' ';
    }
    cout << '\n';
}