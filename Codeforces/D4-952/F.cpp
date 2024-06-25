#include <bits/stdc++.h>
using namespace std;

void solve() {
    int h, n; cin >> h >> n;
    vector<int> a(n), c(n);
    for (auto &x: a) cin >> x;
    for (auto &x: c) cin >> x;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> attacks;
    for (int i = 0; i < n; i++)
        attacks.emplace(1, i);

    for (;;) {
        auto [t, idx] = attacks.top(); attacks.pop();
        if ((h -= a[idx]) <= 0) {
            return void(cout << t << '\n');
        }
        attacks.emplace(t + c[idx], idx);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}