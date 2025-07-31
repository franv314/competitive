#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

void solve() {
    int n; cin >> n;
    map<int, pair<int, int>> ds;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        ds[x] = max(ds[x], {y, i + 1});
    }

    cout << ds.size() << '\n';
    for (auto [_, i]: ds)
        cout << i.second << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}