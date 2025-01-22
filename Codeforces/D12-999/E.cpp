#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    vector<int> masks(1 << m, INT_MAX);
    for (int i = 0; i < (1 << m); i++)
        for (int bit = 0; bit < m; bit++)
            if ((i >> bit) & 1)
                masks[i] &= b[bit];

    vector<deque<int>> order(n, deque<int>(m, INT_MAX));
    for (int i = 0; i < n; i++) {
        for (int mask = 1; mask < (1 << m); mask++) {
            order[i][__builtin_popcount(mask) - 1] = min(order[i][__builtin_popcount(mask) - 1], a[i] & masks[mask]);
        }

        int last = 0;
        for (auto &x: order[i]) { 
            x = a[i] - x - last;
            last += x;
        }

        for (int j = 0; j < m - 1; j++)
            assert(order[i][j] >= order[i][j + 1]);
    }

    priority_queue<pair<int, int>> gains;
    for (int i = 0; i < n; i++)
        gains.emplace(order[i][0], i);

    long long sum = accumulate(a.begin(), a.end(), 0LL);

    for (int _ = 0; _ < k; _++) {
        auto [v, idx] = gains.top(); gains.pop();
        sum -= v;

        order[idx].pop_front();
        if (!order[idx].empty())
            gains.emplace(order[idx][0], idx);
    }

    cout << sum << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
