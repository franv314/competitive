#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> deg(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        deg[u - 1]++;
        deg[v - 1]++;
    }

    int dir = 0;
    for (auto x: deg) {
        dir += max(0, x - 2);
    }

    cout << 1 + (dir + 1) / 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}