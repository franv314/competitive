#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, a, b; cin >> n >> k >> a >> b;
    a--, b--;
    vector<pair<int64_t, int64_t>> cities(n);
    for (auto &[x, y]: cities) cin >> x >> y;

    int64_t dir = abs(cities[a].first - cities[b].first) + abs(cities[a].second - cities[b].second);
    int64_t mi_to = 1e18, mi_from = 1e18;

    for (int i = 0; i < k; i++) {
        mi_to = min(mi_to, abs(cities[i].first - cities[b].first) + abs(cities[i].second - cities[b].second));
        mi_from = min(mi_from, abs(cities[i].first - cities[a].first) + abs(cities[i].second - cities[a].second));
    }
    cout << min(dir, mi_to + mi_from) << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}