#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += a[i] > a[(i + 1) % n];
    }

    cout << (cnt > 1 ? "No\n" : "Yes\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}