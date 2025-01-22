#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, l, r; cin >> n >> l >> r;
    l--;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    sort(a.begin(), a.begin() + l);
    sort(a.begin() + l, a.begin() + r, greater());
    sort(a.begin() + r, a.end());

    long long sum = accumulate(a.begin() + l, a.begin() + r, 0LL);

    long long best_l = 0, best_r = 0;
    long long acc = 0;
    for (int i = 0; i < min(l, r - l); i++) {
        acc += a[i] - a[l + i];
        best_l = min(best_l, acc);
    }

    acc = 0;
    for (int i = 0; i < min(r - l, n - r); i++) {
        acc += a[r + i] - a[l + i];
        best_r = min(best_r, acc);
    }

    cout << sum + min(best_l, best_r) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
