#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n - 1), b(n);

    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;
    a.insert(a.begin(), -1);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int l = 0;
    for (int wpos = 0; wpos < n; wpos++) {
        while (check())
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}