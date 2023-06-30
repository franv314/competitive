#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, d, w; cin >> n >> k >> d >> w;
    vector<int> t(n);
    for (auto &x: t) cin >> x;

    int opened_at = -1e8, remaining;
    int used = 0;

    for (auto x: t) {
        if (x - opened_at > d || remaining <= 0) {
            used++;
            opened_at = x + w;
            remaining = k;
        }
        remaining--;
    }
    cout << used << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}