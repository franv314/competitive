#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto &e: a) cin >> e;
    a.insert(a.begin(), 0);

    for (int i = n; i >= 0; i--) {
        a.push_back(2 * x - a[i]);
    }

    int ma = 0;
    for (int i = 0; i < a.size() - 1; i++) {
        ma = max(ma, a[i + 1] - a[i]);
    }
    cout << ma << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}