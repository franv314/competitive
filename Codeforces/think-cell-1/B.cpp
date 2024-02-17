#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    int lo = 1, hi = n;

    for (int i = 0; i < n; i++) {
        if (i & 1) cout << hi-- << ' ';
        else cout << lo++ << ' ';
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}