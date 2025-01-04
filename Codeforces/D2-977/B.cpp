#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x; cin >> n >> x;
    map<int, multiset<int, greater<int>>> equiv;
    for (int _ = 0; _ < n; _++) {
        int v; cin >> v;
        equiv[v % x].insert(v);
    }

    for (int i = 0; i <= n; i++) {
        auto& s = equiv[i % x];
        auto it = s.lower_bound(i);

        if (it != s.end()) {
            s.erase(it);
        } else {
            return void(cout << i << '\n');
        }
    }
    unreachable();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}